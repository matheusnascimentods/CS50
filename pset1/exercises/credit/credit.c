#include <stdio.h>
#include <cs50.h>

long input(void);
int get_decimals(int number, int decimal);

int main(void)
{
    long number = input();

    printf("%i", n);
}

long input(void)
{
    long number;

    do
    {
        number = get_long("Numero: ");
    }
    while (number <= 0);

    return number;
}

int get_decimals(int number, int decimal)
{
    while(number >= decimal) {
        number /= decimal;
    }

    return number;
}