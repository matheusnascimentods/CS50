#include <stdio.h>
#include <cs50.h>

int input(string message) ;

int main(void)
{
    int start, end = 0;
    int years = 0;

    start = input("Start: ");

    do
    {
        end = input("End: ");
    }
    while (start > end);


    while (end > start)
    {
        start = start + (start / 3) - (start / 4);
        years++;
    }

    printf("Years: %i\n", years);

}

int input(string message)
{
    int value;
    do
    {
        value = get_int("%s", message);
    }
    while (value < 9);

    return value;
}