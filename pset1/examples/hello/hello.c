#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // A função get_string coleta uma string e a guarda em uma varíavel
    string answer = get_string("What's your name? \n");
    printf("Hello %s\n", answer);
}