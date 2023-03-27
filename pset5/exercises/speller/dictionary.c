// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
#define N 26

// Hash table
node *table[N];

// Varíaveis necessárias
unsigned int hash_value;
unsigned int word_count;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    hash_value = hash(word);
    node *list = table[hash_value];

    for (node *i = list; i != NULL; i = i->next)
    {
        int result = strcasecmp(i->word, word);

        if (result == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned long total = 0;

    for (int i = 0, size = strlen(word); i < size; i++)
    {
        total += tolower(word[i]);
    }

    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        printf("Não deu pra abrir o dicíonario\n");
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            printf("Não foi possivel criar o nó necessário.\n");
            return false;
        }

        strcpy(n->word, word);
        hash_value = hash(word);

        n->next = table[hash_value];
        table[hash_value] = n;

        word_count++;

    }
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (word_count > 0)
    {
        return word_count;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *list = table[i];

        while (list != NULL)
        {
            node *tmp = list;
            list = list->next;
            free(tmp);
        }

        if (list == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
