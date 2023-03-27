#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char answer = get_char("Você concorda? [s/n] ");

    if (answer == 's' || answer == 'S')
    {
        printf("Aceito\n");
    }
    else {
        printf("Negado\n");
    }
}