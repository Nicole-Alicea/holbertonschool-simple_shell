#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <ctype.h> /* Include ctype.h for isspace */

extern char **environ;

int main(void)
{
    char *command = NULL, *cmd, *arg, *start, *end;
    size_t len = 0;
    ssize_t nread;
    int is_interactive, i;
    char fullpath[MAX_PATH_LENGTH];
    pid_t pid;
    char *argv[3];  /* Adjusted for possible argument */

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

        /* Trim leading and trailing spaces */
        start = command;
        end = command + strlen(command) - 1;
        while (*start && isspace((unsigned char)*start)) start++;
        while (end > start && isspace((unsigned char)*end)) end--;
        *(end + 1) = '\0';

        if (*start == '\0') /* Only spaces */
        {
            continue; /* Skip execution and prompt again */
        }

        cmd = strtok(start, " ");
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

        /* Check if cmd is a path */
        if (cmd[0] == '.' || cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '.'))
        {
            strcpy(fullpath, cmd); /* Use cmd as the path */
        }
        else if (!find_command_in_path(cmd, fullpath)) /* Handle PATH */
        {
            fprintf(stderr, "Command not found: %s\n", cmd);
            continue;
        }

        pid = fork();
        if (pid == 0) /* Child process */
        {
            argv[0] = fullpath;
            argv[1] = arg;
            argv[2] = NULL;
            execve(fullpath, argv, environ);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0) /* Parent process */
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
