// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
 const unsigned int N = 100;

// Hash table
node *table[N];
int d_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    uint16_t hash_v = hash(word);
    node *x = table[hash_v];

    while( x != NULL)
    {
        if (strcasecmp (word , x -> word) == 0)
        {
            return true;
        }

        x = x -> next;
    }

    return false;
}

//Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    unsigned int hash = 0;
    int c= 0;

    while (c == *word++)
        hash += c;

    return (hash*hash) % N ;

}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dictionary_pointer = fopen(dictionary,"r");

    if (dictionary == NULL)
    {
        printf("cant load %s\n",dictionary);

    }

    char next_w[LENGTH + 1];
    while (!(fscanf(dictionary_pointer,"%s", next_w) == EOF))
    {
        node *x = malloc(2*sizeof(node));

        if (x == NULL)
        {
            return false;
        }
        strcpy (x ->word ,next_w);
        uint16_t hash_v = hash(next_w);

        x ->next = table[hash_v];
        table[hash_v] = x;

        d_size++;
    }


    fclose(dictionary_pointer);


    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return d_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for ( int i = 0 ; i < N ; i++)
    {
        node *z = table[i];

        while (z != NULL)
        {
            node *buffer = z;
           z = z -> next;
            free(buffer);
        }

        if (z == NULL && i == N-1)
        {
            return true;
        }
    }
    return false;
}
