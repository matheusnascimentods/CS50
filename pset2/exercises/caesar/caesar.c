#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2 && isdigit(*argv[1]))
    {
        string s = get_string("plaintext: ");
        int k = atoi(argv[1]);

        printf("ciphertext: ");

        for (int i = 0, n = strlen(s); i < n; i++)
        {
            char c = s[i];

            if (c >= 'a' && c <= 'z')
            {
                printf("%c", (((s[i] - 'a') + k) % 26) + 'a');
            }

            else if (c >= 'A' && c <= 'Z')
            {
                printf("%c", (((s[i] - 'A') + k) % 26) + 'A');
            }

            else
            {
                printf("%c", s[i]);
            }
        }

        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}