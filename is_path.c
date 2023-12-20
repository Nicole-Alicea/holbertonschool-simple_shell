#include "main.h"
#include <string.h>

/**
 * is_path - Checks if a command string is a path
 * @cmd: The command string to check
 *
 * Description: Determines whether a given command string
 * represents a relative or absolute path. This function checks
 * if the command begins with '.', '/', or contains a '/',
 * indicating it is a path.
 *
 * Return: 1 if it's a path, 0 otherwise.
 */
int is_path(char *cmd) {
  return (cmd[0] == '.' || cmd[0] == '/' || strstr(cmd, "/"));
}
