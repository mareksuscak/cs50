// Prompts user for a sequence of notes with which to synthesize a song

#include <cs50.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"
#include "wav.h"

int main(int argc, string argv[])
{
    // Check command line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: synthesize FILE\n");
        return 1;
    }
    string filename = argv[1];

    // Open file for writing
    song s = song_open(filename);

    // Expect notes from user until EOF
    while (true)
    {
        // Expect note
        string line = get_string("");

        // Check for EOF
        if (line == NULL)
        {
            break;
        }

        // Check if line is rest
        if (is_rest(line))
        {
            rest_write(s, 1);
        }
        else
        {
            // Parse line into note and duration
            string note = strtok(line, "@");
            string fraction = strtok(NULL, "@");

            // Write note to song
            note_write(s, frequency(note), duration(fraction));
        }
    }

    // Close file
    song_close(s);
}
