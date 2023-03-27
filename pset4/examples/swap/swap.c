#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 98;
    int y = 11;

    printf("x é %i e y é %i\n", x, y);

    swap(&x, &y);

    printf("x é %i e y é %i\n", x, y);
}

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}