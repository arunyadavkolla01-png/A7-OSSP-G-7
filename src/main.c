#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/shell.h"
#include "../include/auth.h"
#include "../include/input.h"


int main()
{
    char username[MAX_USERNAME];
    char *command;

    /*
     * ================================
     * USER AUTHENTICATION
     * ================================
     */

    if (!authenticate_user(username))
    {
        printf("\n=====================================\n");
        printf("       LOGIN FAILED\n");
        printf("=====================================\n");

        printf("\nInvalid username or password.\n");
        printf("Exiting Multi-User Linux Shell...\n");

        return 1;
    }


    /*
     * ================================
     * LOGIN SUCCESSFUL
     * ================================
     */

    printf("\n=====================================\n");
    printf("       LOGIN SUCCESSFUL\n");
    printf("=====================================\n");

    printf("\nWelcome, %s!\n", username);


    /*
     * ================================
     * START SHELL
     * ================================
     */

    printf("\n=====================================\n");
    printf(" %s Version %s\n", SHELL_NAME, VERSION);
    printf("=====================================\n");


    /*
     * ================================
     * REPL LOOP
     * ================================
     *
     * READ
     * EVALUATE
     * PRINT
     * LOOP
     */

    while (1)
    {
        /*
         * Display user-specific prompt.
         */
        printf("\n%s@MultiUserShell> ", username);

        /*
         * Read command using dynamic memory.
         */
        command = read_line();


        /*
         * Check for exit.
         */
        if (strcmp(command, "exit") == 0)
        {
            free(command);

            printf("\nUser %s logged out.\n", username);

            break;
        }


        /*
         * Ignore empty commands.
         */
        if (strlen(command) == 0)
        {
            free(command);

            continue;
        }


        /*
         * Process command.
         *
         * Currently we display the
         * entered command.
         */
        printf("Command received: %s\n", command);


        /*
         * Release dynamically allocated
         * memory.
         */
        free(command);
    }


    printf("\nThank you for using MultiUserShell.\n");

    return 0;
}
