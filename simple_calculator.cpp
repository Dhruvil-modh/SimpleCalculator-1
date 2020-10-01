/* This is a Simple Calculator 
Author : Razeza
On Date  .......
*/
#include <cstdlib>
#include "stdio.h"

const char*  s        = nullptr;
size_t       size     = 0;
const char*  file_in  = "in.txt";
const size_t Max_size = 1000;

int GetG (const char* str);
int GetE ();
int GetT ();
int GetP ();
int GetN ();
inline void Skip_spaces ();

#define s_plus s++, size++;

int main ()
{
    char str[Max_size] = {};

    while (*str != 'E')
    {
        printf ("\n");
        fscanf (stdin, " %[^\n]", str);
        printf ("%d", GetG (str));
    }
}

inline void Skip_spaces ()
{
    if (*s == ' ' && size < Max_size)
        s_plus
}

int GetN ()
{
    Skip_spaces ();

    int val = 0;
    const char* s_old = s;

    while (*s >= '0' && *s <= '9')
    {
        val = val * 10 + (*s - '0');
        s_plus
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
    Skip_spaces ();

    int val = 0;

    if (*s == '(')
    {
        s_plus
        val = GetE ();

        Skip_spaces ();

        if (*s == ')')
            s_plus
        else
        {
            printf ("Syntax Error");
            exit (3);
        }
    }
    else
    {
        val = GetN ();

        Skip_spaces ();
    }

    return val;
}

int GetT ()
{
    Skip_spaces ();

    int val = 0;
    val = GetP ();

    Skip_spaces ();

    while (*s == '*' || *s == '/')
    {
        char op = *s;
        s_plus

        int val2 = GetP ();

        Skip_spaces ();

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
    Skip_spaces ();

    int val = 0;
    val = GetT ();

    Skip_spaces ();

    while (*s == '+' || *s == '-')
    {
        char op = *s;
        s_plus

        int val2 = GetT ();

        Skip_spaces ();

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

    Skip_spaces ();
    int val = GetE ();

    if (*s != '\0')
    {
        printf ("Syntax Error");
        exit (3);
    }

    return val;
}
