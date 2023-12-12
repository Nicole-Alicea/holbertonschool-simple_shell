#include "main.h"

/**
 * execve - Responsible for handling the command execution
 * @argv: argument vector
 *
 * Return: void
 */

void execve(char **argv)
{
	char *command = NULL;

	if (argv)
	{
		command = argv[0];

		if (execve(command, argv, NULL) == -1)
		{
			perror("Error\n);
		};
	}
}

