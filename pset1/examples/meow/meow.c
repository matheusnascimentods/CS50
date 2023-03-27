#include <stdio.h>

void meow(int counter);

int main(void)
{
    meow(5);
}

void meow(int counter)
{
    for(int i = 0; i < counter; i++)
    {
        printf("meow\n");
    }
}