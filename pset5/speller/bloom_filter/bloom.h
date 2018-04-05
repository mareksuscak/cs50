#ifndef BLOOM_H
#define BLOOM_H

#include <stddef.h>
#include <stdbool.h>

typedef unsigned long (*hash_function)(const void *data);
typedef struct bloom_filter *bloom_t;

bloom_t bloom_create(size_t size);
bool bloom_add_hash(bloom_t filter, hash_function func);
void bloom_insert(bloom_t filter, const void *item);
bool bloom_find(bloom_t filter, const void *item);
void bloom_free(bloom_t filter);

#endif // BLOOM_H
