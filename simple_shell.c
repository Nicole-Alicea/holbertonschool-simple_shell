#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

extern char **environ;

/* Main function of the shell */

int main(void)
{
    char *command = NULL, *cmd, *arg;
    size_t len = 0;
    ssize_t nread;
    int is_interactive, i;
    char fullpath[MAX_PATH_LENGTH];
    pid_t pid;
    char *argv[2];

    is_interactive = isatty(STDIN_FILENO);

    while (1)
    {
        if (is_interactive)
        {
            printf("simple_shell_NJR($) ");
        }

        nread = getline(&command, &len, stdin);
        if (nread == -1)
        {
            if (is_interactive)
            {
                printf("\n");
            }
            break;
        }

        if (command[nread - 1] == '\n')
        {
            command[nread - 1] = '\0';
        }

        cmd = strtok(command, " ");
        arg = strtok(NULL, " ");

        if (cmd && strcmp(cmd, "cat") == 0)
        {
            if (arg == NULL)
            {
                fprintf(stderr, "cat: Missing file name\n");
            }
            else
            {
                handle_cat(arg);
            }
            continue;
        }

        if (strcmp(cmd, "exit") == 0)
        {
            free(command);
            exit(0);
        }

        if (strcmp(cmd, "env") == 0)
        {
            i = 0;
            while (environ[i] != NULL)
            {
                printf("%s\n", environ[i]);
                i++;
            }
            continue;
        }

        if (!find_command_in_path(cmd, fullpath))
        {
            fprintf(stderr, "Command not found: %s\n", cmd);
            continue;
        }

        pid = fork();
        if (pid == 0)
        {
            argv[0] = cmd;
            argv[1] = NULL;
            execve(fullpath, argv, environ);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
        {
            int status;
            waitpid(pid, &status, 0);
        }
        else
        {
            perror("fork");
        }
    }

    free(command);
    return (0);
}

  
