#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *list = malloc(3 * sizeof(int));

    list[0] = 1997;
    list[1] = 1998;
    list[2] = 2000;

    list = realloc(list, 4 * sizeof(int));
    list[3] = 2011;

    for (int i = 0; i < 4; i++)
    {
        printf("list[%i] = %i\n", i, list[i]);
    }

    free(list);
}