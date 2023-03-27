#include <stdio.h>
#include <cs50.h>

int get_number(void);

int main(void)
{
    int width = get_number();

    for (int i = 1; i <= width; i++)
    {
        for (int j = width - i; j >= 1; j--)
        {
            printf(" ");
        }

        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        printf(" ");

        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}

int get_number(void)
{
    int n;
    do
    {
        n = get_int("Informe um numero entre 1 e 8: ");
    }
    while (n < 1 || n > 8);

    return n;
}