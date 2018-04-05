#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

#define MAX_CHILDREN_LENGTH 27

typedef struct trie_node *trie_t;

// Prototypes
trie_t trie_create(void);
bool trie_insert(trie_t root, const char *key);
bool trie_find(trie_t root, const char *key);
void trie_free(trie_t root);

#endif // TRIE_H
