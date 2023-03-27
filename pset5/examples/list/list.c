#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{

    node *list = NULL;
    node *n = malloc(sizeof(node));

    if (n == NULL)
    {
        return 1;
    }

    n->number = 1997;
    n->next = NULL;

    list = n;

    n = malloc(sizeof(node));

    if (n == NULL)
    {
        free(list);
        return 1;
    }

    n->number = 1998;
    list->next = n;

    n = malloc(sizeof(node));

    if (n == NULL)
    {
        free(list->next);
        free(list);
        return 1;
    }

    n->number = 2000;
    n->next = NULL;

    list->next->next = n;

    int number = 1997;

    for (node *i = list; i != NULL; i = i->next)
    {
        if(i->number ==number)
        {
            printf("Is equal\n");
        }
    }

    while (list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }
}