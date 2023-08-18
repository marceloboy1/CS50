// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
#define N 676

// Hash table
node *table[N];

int counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    for (node *tmp = table[hash(word)]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int i = 0;
    if (isalpha(word[1]))
    {
        i =  ((tolower(word[0])-97)*26) + tolower(word[1])-97;
    }
    else
    {
        i = (tolower(word[0])-97)*26;

    }
    return i;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Erro 2");
        return false;
    }

    char word[LENGTH + 1];
    int i = 0;
    int totalWords = 0;
    //read the file
    while (fscanf(dict, "%s", word) == 1)
    {
        i = hash(word);
        counter++;

        //write the word in a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("ERRO 1");
            return  false;
        }
        strcpy(n->word,  word);
        n->next = NULL;

        //writes the first node of table

        if (table[i] == NULL)
        {
            table[i] = n;
        }

        //writes other elements of the chain
        else
        {
            n->next = table[i]->next;
            table[i]->next = n;
        }

    }

    for (node *tmp = table[25]; tmp != NULL; tmp = tmp->next)
    {
        //printf("%s\n", tmp->word);
    }

    //printf("%i\n", totalWords);

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //printf("Counter %i\n", counter);
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = cursor;
        while(cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
        free(tmp);
    }
    return true;
}