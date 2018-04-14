#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>

// Cracked passwords:
//
// anushree:50xcIMJ0y.RXo => YES
// brian:50mjprEcqC/ts => CA
// bjbrown:50GApilQSG3E2 => UPenn
// lloyd:50n0AAUD.pL8g => lloyd
// malan:50CcfIk1QrPr6 => maybe
// maria:509nVI8B9VfuA => TF
// natmelo:50JIIyhDORqMU => nope
// rob:50JGnXUgaafgc => ROFL
// stelios:51u8F0dkeDSbY => NO
// zamyla:50cI2vYkF0YU2 => LOL

/**
 * Analysis:
 *
 * X\0____
 * XX\0___
 * XXX\0__
 * XXXX\0_
 * XXXXX\0
 */

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: crack <hash>\n");
        return 1;
    }

    // TODO: how can i compute the length of the string below?
    const int letters_count = 57;

    // TODO: possible improvement => https://en.wikipedia.org/wiki/Letter_frequency
    string letters = "\0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string hash = argv[1];

    char salt[3];
    memcpy(salt, hash, 2);
    salt[2] = '\0';

    char key_candidate[6] = "\0\0\0\0\0\0";

    for (int fifth = 0; fifth < letters_count; fifth++)
    {
        for (int fourth = 0; fourth < letters_count; fourth++)
        {
            for (int third = 0; third < letters_count; third++)
            {
                for (int second = 0; second < letters_count; second++)
                {
                    for (int first = 1; first < letters_count; first++)
                    {
                        key_candidate[0] = letters[first];
                        key_candidate[1] = letters[second];
                        key_candidate[2] = letters[third];
                        key_candidate[3] = letters[fourth];
                        key_candidate[4] = letters[fifth];

                        if (strcmp(crypt(key_candidate, salt), hash) == 0)
                        {
                            printf("%s\n", key_candidate);
                            return 0;
                        }
                    }
                }
            }
        }
    }

    printf("Password couldn't be cracked!");
    return 2;
}
