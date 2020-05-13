#include <cstdlib>
#include <cstdio>

enum tree {
    RIGHT         = 0,
    LEFT          = 1,
    PUT_OK        = 10,
    ADRESS_ERROR  = -1,
    SIDE_ERROR    = - 2,
    POISON        = -91,
    OK            = 111,
    MAX_SIZE_LINE = 100,
    MAX_LENGTH    = 10,
    END           = 4565,
    NOTHING       = -228
};


struct element {
    char   what;
    int    number;
    struct element* prev;
    struct element* left;
    struct element* right;
};


#define NullPTRRRRRR_YA_SGOREL(what)                                \
{                                                                   \
    if (what == nullptr)                                            \
    {                                                               \
        printf ("ERRRRORRR NUUUUULPTRRRRRRRR!!!!!!!!!!!");          \
        return ADRESS_ERROR;                                        \
    }                                                               \
}

struct element* CreateElement (char what, double number = 0)
{
    struct element* new_elem = (struct element*) calloc (1, sizeof (struct element));

    new_elem->what   = what;
    new_elem->number = number;
    new_elem->prev   = nullptr;
    new_elem->right  = nullptr;
    new_elem->left   = nullptr;

    return new_elem;
}


int PaintTree_s (element* node, FILE* out);

int Merge (struct element* what, struct element* node, int side)
{
    NullPTRRRRRR_YA_SGOREL (node);
    NullPTRRRRRR_YA_SGOREL (what);

    if ((side != RIGHT) && (side != LEFT))
    {
        printf ("ERROR SIDE IS NOT RIGHT");
        return SIDE_ERROR;
    }

    struct element* tmp = nullptr;

    what->prev = node;

    if (side == RIGHT)
    {
        node->right = what;
    }

    if (side == LEFT)
    {
        node->left = what;
    }
}

int DeleteUnderNode (struct element* node)
{
    NullPTRRRRRR_YA_SGOREL (node)

    if (node->right != nullptr)
    {
        DeleteUnderNode (node->right);
        node->right->number   = POISON;
        node->right->what     = POISON;

        free (node->right);
        node->right = nullptr;
    }

    if (node->left != nullptr)
    {
        DeleteUnderNode (node->left);

        node->left->number   = POISON;
        node->left->what     = POISON;

        free (node->left);
        node->left = nullptr;
    }

}

void DeleteTree (struct element* node)
{
    DeleteUnderNode (node);

    node->number   = POISON;
    node->what     = POISON;
    node->prev     = nullptr;
    node->left     = nullptr;
    node->right    = nullptr;

    free (node);
}

int Announce (struct element* node, FILE* out)
{
    NullPTRRRRRR_YA_SGOREL (node)

    fprintf (out, "Node%p [shape=record,label=\"{  adress = %p | { type = %d | number = %.3lf } | prev = %p |{ <l%p> left = %p| <r%p> right = %p  }}\"];\n",
             node, node, node->what, node->number, node->prev, node, node->left, node, node->right);

    if (node->right != nullptr)
    {
        Announce (node->right, out);
    }

    if (node->left != nullptr)
    {
        Announce (node->left, out);
    }
}

int PaintTree (struct element* node, FILE* out)
{
    NullPTRRRRRR_YA_SGOREL (node)

    if (node->left  != nullptr)         fprintf (out, "Node%p:<l%p> -> Node%p:<%p>;\n", node, node, node->left,  node->left);
    if (node->right != nullptr)         fprintf (out, "Node%p:<r%p> -> Node%p:<%p>;\n", node, node, node->right, node->right);
    if (node->prev  != nullptr)         fprintf (out, "Node%p -> Node%p;\n", node, node->prev);

    if (node->right != nullptr)
    {
        PaintTree (node->right, out);
    }

    if (node->left != nullptr)
    {
        PaintTree (node->left, out);
    }
}

int Dump (struct element* node)
{
    NullPTRRRRRR_YA_SGOREL (node)

    FILE* out = fopen ("tree.dot", "w");

    fprintf (out, "digraph structs {\nrankdir=HR;\n");

    Announce (node, out);
    PaintTree (node, out);

    fprintf (out, "\n}");

    fclose (out);

    system ("D:\\Graphiz\\bin\\dot.exe tree.dot -T png -o tree.png");
    system ("tree.png");
}

int Announce_Show (struct element* node, FILE* out)
{
    NullPTRRRRRR_YA_SGOREL (node)


    fprintf (out, "Node%p [shape=\"octagon\",label=\"%s\"];\n", node->what);



    if (node->left != nullptr)
    {
        Announce_Show (node->left, out);
    }

    if (node->right != nullptr)
    {
        Announce_Show (node->right, out);
    }
}

int PaintTree_s (struct element* node, FILE* out)
{
    NullPTRRRRRR_YA_SGOREL (node)


    if (node->left  != nullptr)         fprintf (out, "Node%p -> Node%p;\n", node, node->left);
    if (node->right != nullptr)         fprintf (out, "Node%p -> Node%p;\n", node, node->right);




    if (node->left != nullptr)
    {
        PaintTree_s (node->left, out);
    }

    if (node->right != nullptr)
    {
        PaintTree_s (node->right, out);
    }
}


int ShowTree (struct element* head)
{
    NullPTRRRRRR_YA_SGOREL (head)

    FILE* out = fopen ("show.dot", "w+");

    fprintf (out, "digraph structs {\nrankdir=HR;\n");

    Announce_Show (head, out);

    PaintTree_s (head, out);

    fprintf (out, "\n}");

    fclose (out);

    system ("D:\\Graphiz\\bin\\dot.exe show.dot -T png -o show.png");
    system ("show.png");

}
