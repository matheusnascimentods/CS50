#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char ALPHABET[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }

    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }

    else
    {
        printf("Tie!\n");
    }
}

// Função para calcular os pontos

int compute_score(string word)
{
    int score = 0;

    // For para percorrer cada digito da palavra

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Caso seja uma letra, ela será comparada com cade letra do alfabeto para determinar a sua pontuação

        if (isalpha(word[i]))
        {
            char c = toupper(word[i]);

            for (int j = 0; j < 26; j++)
            {
                if (ALPHABET[j] == c)
                {
                    score = score + POINTS[j];
                    break;
                }
            }
        }
    }

    return score;
}