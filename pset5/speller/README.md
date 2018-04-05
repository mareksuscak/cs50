C implementations of the spell checker using various data structures to hold the dictionary in memory.
The dictionary contains about 144 thousand unique words. Checked document contains 18 thousand words.

The app was compiled with clang -O3. Allocations and memory consumption were measured by valgrind.


------------------------------     ------------------------------     ------------------------------
| Trie (Prefix Tree)         |     | Hashtable (16384 lines)    |     | Bloom Filter (200kB, 2 HF) |
------------------------------     ------------------------------     ------------------------------
| TIME IN load:         0.09 |     | TIME IN load:         0.02 |     | TIME IN load:         0.02 |
| TIME IN check:        0.02 |     | TIME IN check:        0.02 |     | TIME IN check:        0.00 |
| TIME IN size:         0.00 |     | TIME IN size:         0.00 |     | TIME IN size:         0.00 |
| TIME IN unload:       0.05 |     | TIME IN unload:       0.02 |     | TIME IN unload:       0.00 |
| TIME IN TOTAL:        0.15 |     | TIME IN TOTAL:        0.06 |     | TIME IN TOTAL:        0.02 |
------------------------------     ------------------------------     ------------------------------
| ALLOCS: 367,084            |     | ALLOCS: 143,093            |     | ALLOCS: 6                  |
| MEM: 78 MB (82,227,504 B)  |     | MEM: 8 MB (8,014,232 B)    |     | MEM: 201 kB (201,192 B)    |
------------------------------     ------------------------------     ------------------------------


Problem description:
https://docs.cs50.net/2018/x/psets/5/speller/speller.html

I tweeted this a while ago and was asked to share the code.
https://twitter.com/mareksuscak/status/981692310319763456
