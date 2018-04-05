// Loosely based on http://bit.ly/2ElTko2

#include <stdlib.h>
#include <stdint.h>
#include "jenkins.h"

unsigned long jenkins(const void *_str) {
  const char *key = _str;
  unsigned long hash = 0;

  while (*key)
  {
    hash += *key;
    hash += (hash << 10);
    hash ^= (hash >> 6);
    key++;
  }

  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);

  return hash;
}
