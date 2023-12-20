#include "main.h"

/**
 * handle_environment - This function prints the environment
 * @env: Pointer to the environment
 *
 * Return: void
 */

void handle_environment(char *env[])
{
	int x;

	for (x = 0; env[x] != NULL; x++)
	{
		printf("%s\n", env[x]);
	}
}
