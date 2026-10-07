#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#include "../include/redirect.h"

int execute_redirection(char **args)
{
    int i;

    if (args == NULL || args[0] == NULL)
    {
        return 0;
    }

    for (i = 0; args[i] != NULL; i++)
    {
        /*
         * Output redirection: >
         */
        if (strcmp(args[i], ">") == 0)
        {
            if (args[i + 1] == NULL)
            {
                fprintf(stderr, "Error: Missing output file.\n");
                return 1;
            }

            args[i] = NULL;

            int fd = open(args[i + 1],
                          O_WRONLY | O_CREAT | O_TRUNC,
                          0644);

            if (fd < 0)
            {
                perror("open");
                return 1;
            }

            pid_t pid = fork();

            if (pid < 0)
            {
                perror("fork");
                close(fd);
                return 1;
            }

            if (pid == 0)
            {
                if (dup2(fd, STDOUT_FILENO) < 0)
                {
                    perror("dup2");
                    close(fd);
                    _exit(EXIT_FAILURE);
                }

                close(fd);

                execvp(args[0], args);

                perror("execvp");
                _exit(EXIT_FAILURE);
            }

            close(fd);
            waitpid(pid, NULL, 0);

            return 1;
        }

        /*
         * Append redirection: >>
         */
        if (strcmp(args[i], ">>") == 0)
        {
            if (args[i + 1] == NULL)
            {
                fprintf(stderr, "Error: Missing output file.\n");
                return 1;
            }

            args[i] = NULL;

            int fd = open(args[i + 1],
                          O_WRONLY | O_CREAT | O_APPEND,
                          0644);

            if (fd < 0)
            {
                perror("open");
                return 1;
            }

            pid_t pid = fork();

            if (pid < 0)
            {
                perror("fork");
                close(fd);
                return 1;
            }

            if (pid == 0)
            {
                if (dup2(fd, STDOUT_FILENO) < 0)
                {
                    perror("dup2");
                    close(fd);
                    _exit(EXIT_FAILURE);
                }

                close(fd);

                execvp(args[0], args);

                perror("execvp");
                _exit(EXIT_FAILURE);
            }

            close(fd);
            waitpid(pid, NULL, 0);

            return 1;
        }

        /*
         * Input redirection: <
         */
        if (strcmp(args[i], "<") == 0)
        {
            if (args[i + 1] == NULL)
            {
                fprintf(stderr, "Error: Missing input file.\n");
                return 1;
            }

            args[i] = NULL;

            int fd = open(args[i + 1], O_RDONLY);

            if (fd < 0)
            {
                perror("open");
                return 1;
            }

            pid_t pid = fork();

            if (pid < 0)
            {
                perror("fork");
                close(fd);
                return 1;
            }

            if (pid == 0)
            {
                if (dup2(fd, STDIN_FILENO) < 0)
                {
                    perror("dup2");
                    close(fd);
                    _exit(EXIT_FAILURE);
                }

                close(fd);

                execvp(args[0], args);

                perror("execvp");
                _exit(EXIT_FAILURE);
            }

            close(fd);
            waitpid(pid, NULL, 0);

            return 1;
        }

        /*
         * Error redirection: 2>
         */
        if (strcmp(args[i], "2>") == 0)
        {
            if (args[i + 1] == NULL)
            {
                fprintf(stderr, "Error: Missing error output file.\n");
                return 1;
            }

            args[i] = NULL;

            int fd = open(args[i + 1],
                          O_WRONLY | O_CREAT | O_TRUNC,
                          0644);

            if (fd < 0)
            {
                perror("open");
                return 1;
            }

            pid_t pid = fork();

            if (pid < 0)
            {
                perror("fork");
                close(fd);
                return 1;
            }

            if (pid == 0)
            {
                if (dup2(fd, STDERR_FILENO) < 0)
                {
                    perror("dup2");
                    close(fd);
                    _exit(EXIT_FAILURE);
                }

                close(fd);

                execvp(args[0], args);

                perror("execvp");
                _exit(EXIT_FAILURE);
            }

            close(fd);
            waitpid(pid, NULL, 0);

            return 1;
        }
    }

    return 0;
}
