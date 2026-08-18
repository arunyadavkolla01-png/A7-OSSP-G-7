#include <stdio.h>
#include <string.h>

#include "../include/auth.h"
#include "../include/shell.h"

#define USER_FILE "users/users.txt"


int authenticate_user(char *username)
{
    char input_username[MAX_USERNAME];
    char input_password[MAX_PASSWORD];

    char stored_username[MAX_USERNAME];
    char stored_password[MAX_PASSWORD];

    FILE *file;

    printf("\n=====================================\n");
    printf("       MULTI-USER LINUX SHELL\n");
    printf("=====================================\n");

    printf("\nUsername: ");
    scanf("%49s", input_username);

    printf("Password: ");
    scanf("%49s", input_password);

    /*
     * Remove remaining characters
     * from the input buffer.
     */
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* Clear input buffer */
    }

    /*
     * Open user database.
     */
    file = fopen(USER_FILE, "r");

    if (file == NULL)
    {
        printf("\nError: Unable to open user database.\n");
        return 0;
    }

    /*
     * Read users from users.txt.
     */
    while (fscanf(file, "%49[^:]:%49s",
                  stored_username,
                  stored_password) == 2)
    {
        /*
         * Check username and password.
         */
        if (strcmp(input_username, stored_username) == 0 &&
            strcmp(input_password, stored_password) == 0)
        {
            strcpy(username, stored_username);

            fclose(file);

            return 1;
        }
    }

    fclose(file);

    return 0;
}
