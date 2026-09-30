#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/shell.h"
#include "../include/input.h"
#include "../include/parser.h"
#include "../include/process.h"
#include "../include/builtin.h"
#include "../include/signals.h"
#include "../include/pipes.h"

int main(void)
{
    char *line;
    char **tokens;

    initialize_signals();

    printf("=====================================\n");
    printf("Multi-User Shell - ShellForge\n");
    printf("Week 7: Pipe Support\n");
    printf("=====================================\n");

    while (1)
    {
        printf("myshell> ");
        fflush(stdout);

        line = read_line();

        if (line == NULL)
        {
            break;
        }

        /* Check whether the input contains a pipe. */
        char *pipe_position = strchr(line, '|');

        if (pipe_position != NULL)
        {
            /* This implementation supports one pipe only. */
            if (strchr(pipe_position + 1, '|') != NULL)
            {
                fprintf(stderr,
                        "Only one pipe is supported at a time.\n");
                free(line);
                continue;
            }

            /* Split the input into two commands. */
            *pipe_position = '\0';

            char **cmd1 = parse_line(line);
            char **cmd2 = parse_line(pipe_position + 1);

            if (cmd1 == NULL || cmd2 == NULL ||
                cmd1[0] == NULL || cmd2[0] == NULL)
            {
                fprintf(stderr, "Invalid pipe command\n");
            }
            else
            {
                execute_pipe(cmd1, cmd2);
            }

            free_tokens(cmd1);
            free_tokens(cmd2);
            free(line);

            continue;
        }

        /* Parse a normal, non-piped command. */
        tokens = parse_line(line);

        if (tokens[0] != NULL)
        {
            /* Built-ins execute in the shell process. */
            if (execute_builtin(tokens) == 0)
            {
                execute(tokens);
            }
        }

        free_tokens(tokens);
        free(line);
    }

    printf("\nGoodbye!\n");

    return 0;
}
