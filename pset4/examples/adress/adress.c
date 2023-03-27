#include <stdio.h>

int main(void)
{
    int n = 98;
    int *p = &n;

    printf("A localização da variavel n é %p\n", &n);
    printf("%i\n", *p);
}