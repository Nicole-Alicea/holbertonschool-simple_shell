#include "main.h"

/**
 * find_command_in_path - Find command in current path
 * @cmd: String representing the command to be found
 * @fullpath: Pointer to where the full path of the command will be
 * stored if found
 *
 * Return: 1 if the command was found and 0 if it wasn't
 */

int find_command_in_path(char *cmd, char *fullpath)
{
	struct stat st;
	char *path, *token, pth[MAX_PATH_LENGTH];

	/* Check if cmd is an absolute path */
	if (cmd[0] == '/')
	{
		if (stat(cmd, &st) == 0 && S_ISREG(st.st_mode))
		{
			strcpy(fullpath, cmd);
			return (1);
		}
		else
		{
			return (0);
		}
	}
	path = getenv("PATH");

	if (path == NULL)
	{
		fprintf(stderr, "Error: PATH environment variable not set.\n");
		return (0);
	}

	strcpy(pth, path);
	token = strtok(pth, ":");

	while (token != NULL)
	{
		if (strlen(token) + strlen(cmd) + 2 <= MAX_PATH_LENGTH)
		{
			sprintf(fullpath, "%s/%s", token, cmd);

			if (stat(fullpath, &st) == 0 && S_ISREG(st.st_mode))
			{
				return (1); /* Command found */
			}
		}
		token = strtok(NULL, ":");
	}
	return (0); /* Command not found */
}
