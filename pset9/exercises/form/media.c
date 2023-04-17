#include <stdio.h>
#include <cs50.h>

int main(void)
{
    float notas[3];

    for (int i = 0; i < 3; i++)
    {
        float nota = get_float("nota: ");
        notas[i] = nota;
    }

    float media = (notas[0] + notas[1] + notas[2]) / 3.0;
    printf("Média: %f", media);
}