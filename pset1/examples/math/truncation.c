#include <stdio.h>
#include <cs50.h>

int main(void)
{

    int x = get_int("x: ");
    int y = get_int("y: ");
    float z = (float) x / (float) y;

    printf("%i / %i = %f\n", x, y, z);
}