// Adapted from http://bit.ly/2GE2nTc

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "bloom.h"

struct bloom_hash
{
    hash_function func;
    struct bloom_hash *next;
};

struct bloom_filter
{
    struct bloom_hash *func;
    void *bits;
    size_t size;
};

// Allocates a memory segment for a new Bloom Filter and resets bits to zeroes.
bloom_t bloom_create(size_t size)
{
  bloom_t res = calloc(1, sizeof(struct bloom_filter));

  res->size = size;
  res->bits = malloc(size);

  memset(res->bits, 0, size);

  return res;
}

// Adds a custom hashing function to the bloom filter.
bool bloom_add_hash(bloom_t filter, hash_function func)
{
  struct bloom_hash *last = filter->func;

  struct bloom_hash *h = calloc(1, sizeof(struct bloom_hash));
  if (h == NULL)
  {
    return false;
  }

  h->func = func;

  while (last && last->next)
  {
    last = last->next;
  }

  if (last)
  {
    last->next = h;
  }
  else
  {
    filter->func = h;
  }

  return true;
}

// Inserts an item into the set represented by the Bloom Filter
void bloom_insert(bloom_t filter, const void *item)
{
  struct bloom_hash *h = filter->func;
  uint8_t *bits = filter->bits;

  while (h)
  {
    unsigned long hash = h->func(item);

    hash %= filter->size * 8;
    bits[hash / 8] |= (1 << (hash % 8));
    h = h->next;
  }
}

// Queries the Bloom Filter for an item
bool bloom_find(bloom_t filter, const void *item)
{
  struct bloom_hash *h = filter->func;
  uint8_t *bits = filter->bits;

  while (h)
  {
    unsigned long hash = h->func(item);
    hash %= filter->size * 8;

    if (!(bits[hash / 8] & (1 << (hash % 8))))
    {
      return false;
    }

    h = h->next;
  }

  return true;
}

// Frees the memory allocated in bloom_create
void bloom_free(bloom_t filter)
{
  if (filter)
  {
    while (filter->func)
    {
      struct bloom_hash *h = filter->func;
      filter->func = h->next;
      free(h);
    }

    free(filter->bits);
    free(filter);
  }
}
