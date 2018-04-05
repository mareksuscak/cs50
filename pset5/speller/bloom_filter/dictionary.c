// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "djb2.h"
#include "jenkins.h"
#include "bloom.h"
#include "dictionary.h"

bloom_t bf = NULL;

// Keeps track of the # of words in dictionary
unsigned long words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Converts string to its lowercase representation
    char copy[strlen(word) + 1];
    strcpy(copy, word);
    char *p = copy;
    for ( ; *p; ++p) *p = tolower(*p);

    return bloom_find(bf, copy);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }

    bf = bloom_create(200000);
    if (bf == NULL)
    {
        fclose(file);
        return false;
    }

    // Our new Bloom Filter will use 2 hashing functions.
    // You'll want to experiment with various hashing functions.
    // One option would be to use 128-bit murmur3 and split the hash
    // into two 64-bit hashes. You'd need to hard-code the hashing
    // function in that case. This is a slightly more flexible
    // implementation.

    bloom_add_hash(bf, djb2);
    bloom_add_hash(bf, jenkins);

    char buffer[LENGTH];
    while (fscanf(file, "%s", buffer) != EOF)
    {
        // Dict should contain only lowercase words
        bloom_insert(bf, buffer);

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
    bloom_free(bf);
    return true;
}
