// A simple sound library adapted from Douglas Thain's (dthain@nd.edu)
// wavfile library for CSE 20211 made available under the
// Creative Commons Attribution license.
// https://creativecommons.org/licenses/by/4.0/

#include <cs50.h>
#include <stdio.h>
#include <inttypes.h>

// Representation of a note
typedef struct note
{
    int frequency;
    int duration;
}
note;

// Representation of a song
struct song
{
    string filename;
    note **notes;
    size_t capacity;
    size_t size;
    int duration;
};
typedef struct song *song;

// Adds a note to a song for a given duration (in eighths)
bool note_write(song s, int frequency, int duration);

// Adds a rest to a song for a given duration (in eighths)
bool rest_write(song s, int duration);

// Saves a song to disk
bool song_close(song s);

// Creates a new song
song song_open(string filename);
