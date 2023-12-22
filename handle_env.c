#include "main.h"

/**
 * handle_env - Prints environment variables if the provided command is "env"
 * @cmd: String representing the command to be checked
 *
 * Return: void
 */

void handle_env(char *cmd)
{
	int i;

	if (strcmp(cmd, "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			printf("%s\n", environ[i]);
		}
	}
}
