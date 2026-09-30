#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include "../include/pipes.h"

static void wait_for_child(pid_t pid)
{
    int status;
    pid_t result;

    do
    {
        result = waitpid(pid, &status, 0);
    }
    while (result == -1 && errno == EINTR);

    if (result == -1 && errno != ECHILD)
    {
        perror("waitpid");
    }
}

void execute_pipe(char **cmd1, char **cmd2)
{
    int pipefd[2];
    pid_t pid1;
    pid_t pid2;

    if (cmd1 == NULL || cmd2 == NULL ||
        cmd1[0] == NULL || cmd2[0] == NULL)
    {
        fprintf(stderr, "Invalid pipe command\n");
        return;
    }

    /* Create the communication pipe. */
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return;
    }

    /* Create the first child process. */
    pid1 = fork();

    if (pid1 == -1)
    {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return;
    }

    if (pid1 == 0)
    {
        /* First command writes to the pipe. */
        close(pipefd[0]);

        if (dup2(pipefd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2");
            _exit(EXIT_FAILURE);
        }

        close(pipefd[1]);

        execvp(cmd1[0], cmd1);

        perror("execvp");
        _exit(EXIT_FAILURE);
    }

    /* Create the second child process. */
    pid2 = fork();

    if (pid2 == -1)
    {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);

        wait_for_child(pid1);

        perror("fork");
        return;
    }

    if (pid2 == 0)
    {
        /* Second command reads from the pipe. */
        close(pipefd[1]);

        if (dup2(pipefd[0], STDIN_FILENO) == -1)
        {
            perror("dup2");
            _exit(EXIT_FAILURE);
        }

        close(pipefd[0]);

        execvp(cmd2[0], cmd2);

        perror("execvp");
        _exit(EXIT_FAILURE);
    }

    /* Parent no longer needs the pipe. */
    close(pipefd[0]);
    close(pipefd[1]);

    /* Wait for both commands to finish. */
    wait_for_child(pid1);
    wait_for_child(pid2);
}
