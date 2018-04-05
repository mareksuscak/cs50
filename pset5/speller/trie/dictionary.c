// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "trie.h"
#include "dictionary.h"

trie_t root = NULL;

// Keeps track of the # of words in dictionary
unsigned long words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    return trie_find(root, word);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }

    root = trie_create();
    if (root == NULL)
    {
        return false;
    }

    char buffer[LENGTH];
    while (fscanf(file, "%s", buffer) != EOF)
    {
        if (!trie_insert(root, buffer))
        {
            unload();
            break;
        }

        words++;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    trie_free(root);

    return true;
}
