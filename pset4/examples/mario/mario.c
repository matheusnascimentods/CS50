#include <stdio.h>
#include <cs50.h>

void draw(int h);

int main(void)
{
    int h = get_int("Height: ");

    draw(h);
}

void draw(int h)
{
    for (int i = 1; i <= h; i++)
    {
        for (int j = 0; j < i; j++)
        {
            printf("*");
        }

        printf("\n");
    }
}