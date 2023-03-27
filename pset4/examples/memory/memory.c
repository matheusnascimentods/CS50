#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *x;

    x = malloc(sizeof(int));

    *x = 98;

    printf("%i\n", *x);
}