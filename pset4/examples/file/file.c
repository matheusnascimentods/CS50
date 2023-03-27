#include <string.h>
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    FILE *file = fopen("file.txt", "a");
    if (file == NULL)
    {
        return 1;
    }

    char *text = get_string("Text: ");

    fprintf(file, "%s\n", text);
    fclose(file);
}