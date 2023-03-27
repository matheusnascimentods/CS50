#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int CountWords(char digit);
int CountLetters(char digit);
int CountSentences(char digit);
int Calculate(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");
    int letters, words, sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Estas funções verificam se digito é um espaço, uma letra ou o final de uma frase o contabilizam.
        words = words + CountWords(text[i]);
        letters = letters + CountLetters(text[i]);
        sentences = sentences + CountSentences(text[i]);
    }

    // Somo 1 as palavras para contabilizar a ultima palavra do texto.
    words = words + 1;

    int indice = Calculate(letters, words, sentences);

    if (indice >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (indice < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", indice);
    }

}

int CountWords(char digit)
{
    int digits = 0;

    if (isspace(digit))
    {
        digits = digits + 1;
    }

    return digits;
}

int CountLetters(char digit)
{
    int digits = 0;

    if (isalpha(digit))
    {
        digits = digits + 1;
    }

    return digits;
}

int CountSentences(char digit)
{
    int digits = 0;

    if (digit == '.' || digit == '?' || digit == '!')
    {
        digits = digits + 1;
    }

    return digits;
}

int Calculate(int letters, int words, int sentences)
{
    double L = ((float)letters / (float)words) * 100;
    double S = ((float)sentences / (float)words) * 100;

    double FloatIndex = 0.0588 * L - 0.296 * S - 15.8;
    int IntIndex = round(FloatIndex);

    return IntIndex;
}