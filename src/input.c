#include <stdio.h>
#include <stdlib.h>

#include "../include/input.h"

#define INITIAL_SIZE 64


char *read_line(void)
{
    int size = INITIAL_SIZE;
    int position = 0;
    int ch;

    /*
     * Allocate initial memory.
     */
    char *buffer = malloc(size);

    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        ch = getchar();

        /*
         * Stop when user presses Enter
         * or when EOF is reached.
         */
        if (ch == EOF || ch == '\n')
        {
            buffer[position] = '\0';

            return buffer;
        }

        /*
         * Store character.
         */
        buffer[position++] = ch;

        /*
         * Expand buffer when required.
         */
        if (position >= size - 1)
        {
            size *= 2;

            char *temp = realloc(buffer, size);

            if (temp == NULL)
            {
                free(buffer);

                fprintf(stderr,
                        "Memory reallocation failed\n");

                exit(EXIT_FAILURE);
            }

            buffer = temp;
        }
    }
}
