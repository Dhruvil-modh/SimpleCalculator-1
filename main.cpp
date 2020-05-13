#include <cstdlib>
#include "stdio.h"

const char*  s        = nullptr;
const char*  file_in  = "in.txt";
const size_t Max_size = 1000;

int GetG (const char* str);
int GetE ();
int GetT ();
int GetP ();
int GetN ();

int main ()
{
    FILE* in = fopen (file_in, "r");

    char str[Max_size] = {};
    fscanf (in, "%s", str);
    printf ("%d", GetG (str));
}


int GetN ()
{
    int val = 0;
    const char* s_old = s;

    while (*s >= '0' && *s <= '9')
    {
        val = val * 10 + (*s - '0');
        s++;
    }

    if (s == s_old)
    {
        printf ("Syntax Error");
        exit (3);
    }

    return val;
}

int GetP ()
{
    int val = 0;

    if (*s == '(')
    {
        s++;
        val = GetE ();
        if (*s == ')')
            s++;
        else
        {
            printf ("Syntax Error");
            exit (3);
        }
    }
    else
    {
        val = GetN ();
    }

    return val;
}

int GetT ()
{
    int val = 0;
    val = GetP ();

    while (*s == '*' || *s == '/')
    {
        char op = *s;
        s++;

        int val2 = GetP ();

        if (op == '*')
            val *= val2;
        else
        if (op == '/')
            val /= val2;
        else
        {
            printf ("Syntax Error");
            exit (3);
        }
    }

    return val;
}

int GetE ()
{
    int val = 0;
    val = GetT ();

    while (*s == '+' || *s == '-')
    {
        char op = *s;
        s++;

        int val2 = GetT ();

        if (op == '+')
            val += val2;
        else
            if (op == '-')
                val -= val2;
            else
            {
                printf ("Syntax Error");
                exit (3);
            }
    }

    return val;
}

int GetG (const char* str)
{
    s = str;

    int val = GetE ();

    if (*s != '\0')
    {
        printf ("Syntax Error");
        exit (3);
    }

    return val;
}