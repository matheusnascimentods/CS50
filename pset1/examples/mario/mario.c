#include <stdio.h>
#include <cs50.h>

int main(void)
{

    int w = get_int("Informe a largura: ");
    int h = get_int("Ïnforme a altura: ");

    for (int i = 0; i < h; i++)
    {

        for(int j = 0; j < w; j++)
        {
            printf("#");
        }
        printf("\n");

    }

}