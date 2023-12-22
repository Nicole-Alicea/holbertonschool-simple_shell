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

		printf("Exiting with status %d\n", exit_status);
		exit(exit_status);
	}
	else
	{
		printf("Exiting without parameter\n");
		exit(0);
	}
}
