// A simple sound library adapted from Douglas Thain's (dthain@nd.edu)
// wavfile library for CSE 20211 made available under
// the Creative Commons Attribution license.
// https://creativecommons.org/licenses/by/4.0/

#include <cs50.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "wav.h"

#define WAV_SAMPLES_PER_SECOND 44100
#define BEAT_LEN (WAV_SAMPLES_PER_SECOND / 4)
#define DECAY_DURATION BEAT_LEN / 2
#define DECAY_FACTOR -5
#define SILENCE_DURATION 5
#define VOLUME 32000

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

// Represents a WAV header
struct wav_header
{
    char riff_tag[4];         // "RIFF"
    int32_t riff_length;      // Size of RIFF header
    char wave_tag[4];         // "WAVE"
    char fmt_tag[4];          // "fmt ", start of format data
    int32_t fmt_length;       // Size of fmt subchunk
    int16_t audio_format;     // Audio compression format
    int16_t num_channels;     // Number of audio channels
    int32_t sample_rate;      // Samples of audio per second
    int32_t byte_rate;       // Bytes per second
    int16_t block_align;      // Bytes for one sample
    int16_t bits_per_sample;  // Bits  for one sample
    char data_tag[4];         // "data", start of sound data
    int32_t data_length;      // Size of sound data
};

// Opens a new file and populates it with WAV header
static FILE *wav_open(const char *filename)
{
    struct wav_header header;
    int samples_per_second = WAV_SAMPLES_PER_SECOND;
    int bits_per_sample = 16;
    strncpy(header.riff_tag, "RIFF", 4);
    strncpy(header.wave_tag, "WAVE", 4);
    strncpy(header.fmt_tag, "fmt ", 4);
    strncpy(header.data_tag, "data", 4);
    header.riff_length = 0;
    header.fmt_length = 16;
    header.audio_format = 1;
    header.num_channels = 1;
    header.sample_rate = samples_per_second;
    header.byte_rate = samples_per_second * (bits_per_sample / 8);
    header.block_align = bits_per_sample / 8;
    header.bits_per_sample = bits_per_sample;
    header.data_length = 0;
    FILE *file = fopen(filename, "w+");
    if (!file)
    {
        return NULL;
    }
    fwrite(&header, sizeof(header), 1, file);
    fflush(file);
    return file;
}

// Outputs the contents of a WAV file to disk
static bool wav_write(FILE *file, short data[], size_t length)
{
    size_t items = fwrite(data, sizeof(short), length, file);
    return items == length;
}

// Updates the WAV file header and closes the file
static bool wav_close(FILE *file)
{
    int file_length = ftell(file);
    int data_length = file_length - sizeof(struct wav_header);
    fseek(file, sizeof(struct wav_header) - sizeof(int), SEEK_SET);
    fwrite(&data_length, sizeof(data_length), 1, file);
    int riff_length = file_length - 8;
    fseek(file, 4, SEEK_SET);
    size_t items = fwrite(&riff_length, sizeof(riff_length), 1, file);
    fclose(file);
    return items == 1;
}

// Allocate memory for an empty song, set initial capacity to 16 notes
song song_open(string filename)
{
    // Allocate memory for empty song
    song s = calloc(1, sizeof(struct song));
    if (!s)
    {
        return NULL;
    }

    // Give the song an initial capacity of 16 notes
    s->filename = filename;
    s->capacity = 16;
    s->notes = calloc(s->capacity, sizeof(*s->notes));
    if (!s->notes)
    {
        free(s);
        return NULL;
    }
    s->size = 0;
    return s;
}

// Append note to end of array of notes in song
// Each duration unit is an eighth note at 120bpm
bool note_write(song s, int frequency, int duration)
{
    // Increase size of song if necessary
    if (s->size == s->capacity)
    {
        if (s->capacity > SIZE_MAX / sizeof(*s->notes) / 2)
        {
            return false;
        }
        s->capacity *= 2;
        note **temp = realloc(s->notes, sizeof(*s->notes) * s->capacity);
        if (!temp)
        {
            return false;
        }
        s->notes = temp;
    }

    // Create a new note
    note *n = calloc(1, sizeof(note));
    if (!n)
    {
        return false;
    }
    n->frequency = frequency;
    n->duration = duration;

    // Add note to song
    s->notes[s->size] = n;
    s->duration += duration;
    s->size++;

    return true;
}

// Add a frequency of 0 to represent a rest in the song
bool rest_write(song s, int duration)
{
    return note_write(s, 0, duration);
}

// Compute wavforms based on note frequency and save to disk
bool song_close(song s)
{
    if (!s || !s->size)
    {
        return false;
    }
    FILE *f = wav_open(s->filename);
    if (!f)
    {
        return false;
    }
    short *waveform = calloc(s->duration * BEAT_LEN, sizeof(short));
    if (!waveform)
    {
        return false;
    }
    short *current_sample = waveform;

    // Iterate over notes in the song
    for (size_t i = 0; i < s->size; i++)
    {
        // Compute waveform for note
        note *n = s->notes[i];
        double phase = 0.0;
        double phase_step = n->frequency * 2.0 * M_PI / WAV_SAMPLES_PER_SECOND;
        short *note_end = current_sample + n->duration * BEAT_LEN - SILENCE_DURATION;
        short *decay_start = note_end - DECAY_DURATION;
        for (; current_sample != decay_start; phase += phase_step)
        {
            *current_sample++ = round(VOLUME * sin(phase));
        }
        for (; current_sample != note_end; phase += phase_step)
        {
            double t = (double) (current_sample - decay_start) / BEAT_LEN;
            *current_sample++ = round(VOLUME * pow(M_E, t * DECAY_FACTOR) * sin(phase));
        }

        // Skip over silence at end of note
        current_sample += SILENCE_DURATION;

        // Done with note, free it
        free(n);
    }

    // Output WAV data to file
    bool success = wav_write(f, waveform, s->duration * BEAT_LEN);
    wav_close(f);

    // Free song
    free(s->notes);
    free(s);
    free(waveform);
    return success;
}
