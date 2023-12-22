#include "main.h"

/**
 * handle_exit - Handles the "exit" comand
 * @cmd: String representing the command to be checked
 *
 * Return: void
 */

void handle_exit(char *arg)
{
	int exit_status;

	if (arg != NULL)
	{
		exit_status = atoi(arg);

		exit(exit_status);
	}
	else
	{
		exit(0);
	}
}
