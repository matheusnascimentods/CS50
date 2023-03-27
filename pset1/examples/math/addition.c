#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int x = get_int("Digite um número inteiro: ");

    int y = get_int("Digite outro número inteiro: ");

    printf("A soma destes numeros é %i\n", x + y);
}