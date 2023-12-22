#include "main.h"

/**
 * handle_exit - Handles the "exit" comand
 * @cmd: String representing the command to be checked
 *
 * Return: 0 if the command is "exit", 1 otherwise
 */

int handle_exit(char *arg)
{
	int exit_status = atoi(arg);
	if (arg != NULL)
	{
		exit(exit_status);
	}
	else
	{
		exit(0);
	}
}
