#include "main.h"

/**
 * command_exists - Checks if a command exists at the given path
 * @cmd: Pointer to the command
 *
 * Return: 1 if the file exists and 0 if it doesn't
 */

int command_exists(char *cmd)
{
	struct stat buffer;
	return (stat(cmd, &buffer) == 0);
}
