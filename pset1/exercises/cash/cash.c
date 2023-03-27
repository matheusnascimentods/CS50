#include <stdio.h>
#include <math.h>
#include <cs50.h>

float get_value(void);
int calculate_coins(int cash, int value);

int main(void)
{
    float dollars = get_value();
    int cents = round(dollars * 100);

    int values[] = {25, 10, 5, 1};
    int coins = 0;

    for (int i = 0; i < 4; i++)
    {
        int value = values[i];

        int quantity = calculate_coins(cents, value);
        cents = cents - quantity * value;

        coins += quantity;
    }

    printf("%i\n", coins);
}

float get_value(void)
{
    float value;
    do
    {
        value = get_float("Troco: ");
    }
    while (value <= 0);

    return value;
}

int calculate_coins(int cash, int value)
{
    int coins = cash / value;
    return coins;
}