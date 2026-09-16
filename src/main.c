#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/shell.h"
#include "../include/auth.h"
#include "../include/input.h"
#include "../include/parser.h"
#include "../include/process.h"
#include "../include/builtin.h"

int main()
{
    char username[MAX_USERNAME];
    char *line;
    char **tokens;

    /* Authentication */
    if (!authenticate_user(username))
    {
        printf("\n=====================================\n");
        printf("       LOGIN FAILED\n");
        printf("=====================================\n");

        printf("\nInvalid username or password.\n");
        printf("Exiting MultiUserShell...\n");

        return 1;
    }

    /* Login successful */
    printf("\n=====================================\n");
    printf("       LOGIN SUCCESSFUL\n");
    printf("=====================================\n");

    printf("\nWelcome, %s!\n", username);

    printf("\n=====================================\n");
    printf(" %s Version %s\n", SHELL_NAME, VERSION);
    printf("=====================================\n");

    /* Shell REPL */
    while (1)
    {
        printf("\n%s@MultiUserShell> ", username);

        line = read_line();

        /* Empty command */
        if (strlen(line) == 0)
        {
            free(line);
            continue;
        }

        /* Parse command */
        tokens = parse_line(line);

        /* Built-in or external command */
        if (execute_builtin(tokens) == 0)
        {
            execute(tokens);
        }

        free_tokens(tokens);
        free(line);
    }

    return 0;
}
