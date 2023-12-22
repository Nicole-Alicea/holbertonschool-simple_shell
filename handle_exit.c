#include "main.h"

/**
 * handle_exit - Handles the "exit" comand
 * @cmd: String representing the command to be checked
 *
 * Return: 0 if the command is "exit", 1 otherwise
 */

int handle_exit(char *cmd)
{
	if (strcmp(cmd, "exit") == 0)
	{
		free(cmd);
		return (0);
	}
	return (1);
}
