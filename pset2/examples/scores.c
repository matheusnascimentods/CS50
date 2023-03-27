#include <stdio.h>
#include <cs50.h>

int input(string message);
float average(int scores[], int total);

int main(void)
{
    int total = input("Total de notas: ");
    int scores[total];

    for(int i = 0; i < total; ++i)
    {
        scores[i] = input("Nota: ");
    }

    printf("Average: %.2f\n", average(scores, total));

}

int input(string message)
{
    int number;

    do
    {
        number = get_int("%s", message);
    }
    while(number <= 0);

    return number;
}

float average(int scores[], int total)
{
    int sum = 0;

    for(int i = 0; i < total; ++i)
    {
        sum = sum + scores[i];
    }

    float average = sum / total;
    
    return average;
}