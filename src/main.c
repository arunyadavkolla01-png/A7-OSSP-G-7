#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/auth.h"
#include "../include/input.h"
#include "../include/parser.h"
#include "../include/process.h"
#include "../include/builtin.h"
#include "../include/signals.h"
#include "../include/pipes.h"
#include "../include/redirect.h"
#include "../include/thread.h"

int main(void)
{
    char username[50];

    char *line;
    char **tokens;

    if (authenticate_user(username) == 0)
    {
        printf("\nAuthentication failed.\n");
        printf("Access denied.\n");
        return 1;
    }

    printf("\n=====================================\n");
    printf("      Authentication Successful\n");
    printf("      Welcome, %s!\n", username);
    printf("=====================================\n");

    initialize_signals();
    start_monitor_thread();

    while (1)
    {
        printf("%s@ShellForge> ", username);
        fflush(stdout);

        line = read_line();

        if (line == NULL)
        {
            printf("\n");
            break;
        }

        if (strlen(line) == 0)
        {
            free(line);
            continue;
        }

        char *pipe_position = strchr(line, '|');

        if (pipe_position != NULL)
        {
            if (strchr(pipe_position + 1, '|') != NULL)
            {
                fprintf(stderr,
                        "Error: Only one pipe is supported at a time.\n");

                free(line);
                continue;
            }

            *pipe_position = '\0';

            char **cmd1 = parse_line(line);
            char **cmd2 = parse_line(pipe_position + 1);

            if (cmd1 == NULL ||
                cmd2 == NULL ||
                cmd1[0] == NULL ||
                cmd2[0] == NULL)
            {
                fprintf(stderr, "Error: Invalid pipe command.\n");
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

        tokens = parse_line(line);

        if (tokens == NULL)
        {
            free(line);
            continue;
        }

        if (tokens[0] != NULL)
        {
            if (execute_builtin(tokens) == 0)
            {
                if (execute_redirection(tokens) == 0)
                {
                    execute(tokens);
                }
            }
        }

        free_tokens(tokens);
        free(line);
    }

    printf("\nSession ended for user: %s\n", username);
    printf("Goodbye!\n");

    return 0;
}
