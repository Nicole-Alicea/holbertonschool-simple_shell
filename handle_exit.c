#include "main.h"

/**
 * handle_exit - Handles the "exit" comand
 * @cmd: String representing the command to be checked
 *
 * Return: void
 */

void handle_exit(char *cmd)
{
	char *command = NULL, *start, *end;

	start = command;
	end = command + strlen(command) - 1;
        while (*start && isspace((unsigned char)*start)) start++;
        while (end > start && isspace((unsigned char)*end)) end--;
        *(end + 1) = '\0';

        cmd = strtok(start, " ");

	if (strcmp(cmd, "exit") == 0)
	{
            free(command);
            exit(0);
        }
}
