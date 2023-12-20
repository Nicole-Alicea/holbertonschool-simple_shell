#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>

extern char **environ;

int main(void)
{
    char *command = NULL, *cmd, *arg, *start, *end;
    size_t len = 0;
    ssize_t nread;
    int is_interactive, status;
    pid_t pid;
    char fullpath[MAX_PATH_LENGTH];
    char *argv[3];
    int i;

    is_interactive = isatty(STDIN_FILENO);

    while (1)
    {
        if (is_interactive) {
            printf("simple_shell_NJR($) ");
        }

        nread = getline(&command, &len, stdin);
        if (nread == -1) {
            if (is_interactive) {
                printf("\n");
            }
            break;
        }

        start = command;
        end = command + strlen(command) - 1;
        while (*start && isspace((unsigned char)*start)) start++;
        while (end > start && isspace((unsigned char)*end)) end--;
        *end = '\0';

        if (*start == '\0') continue;

        cmd = strtok(start, " ");
        arg = strtok(NULL, " ");

        if (cmd && strcmp(cmd, "cat") == 0) {
            if (arg == NULL) {
                fprintf(stderr, "cat: Missing file name\n");
            } else {
                handle_cat(arg);
            }
            continue;
        }

        if (strcmp(cmd, "exit") == 0) {
            free(command);
            exit(0);
        }

        if (strcmp(cmd, "env") == 0) {
            for (i = 0; environ[i] != NULL; i++) {
                printf("%s\n", environ[i]);
            }
            continue;
        }

        if (is_path(cmd)) {
            strcpy(fullpath, cmd);
        } else if (!find_command_in_path(cmd, fullpath)) {
            fprintf(stderr, "Command not found: %s\n", cmd);
            continue;
        }

        if (!command_exists(fullpath)) {
            fprintf(stderr, "Command not found: %s\n", fullpath);
            continue;
        }

        pid = fork();
        if (pid == 0) {
            argv[0] = fullpath;
            argv[1] = arg;
            argv[2] = NULL;
            execve(fullpath, argv, environ);
            perror("execve");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            waitpid(pid, &status, 0);
        } else {
            perror("fork");
        }
    }

    free(command);
    return (0);
}
