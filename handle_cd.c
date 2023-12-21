#include "main.h"

/**
 * cd - This function will handle "cd"
 * @path: The path to which you want to change the current working directory
 *
 * Return: 0 Success or -1 upon a failure
 */

int handle_cd(char *path)
{
	char *cmd, *arg;

	cmd = strtok(path, " ");
	arg = strtok(NULL, " ");

	if (strcmp(cmd, "cd") == 0)
	{
		if (arg == NULL || strcmp(arg, "~") == 0 || strcmp(arg, "$HOME") == 0)
		{
			chdir(getenv("HOME"));
		}
		else if (strcmp(arg, "-") == 0)
		{
			char *oldpwd = getenv("OLDPWD");
			if (oldpwd != NULL)
			{
				chdir(oldpwd);
				printf("%s\n", oldpwd);
			}
			else
			{
				fprintf(stderr, "OLDPWD not set\n");
			}
		}
		else if (strcmp(arg, "/tmp") == 0)
		{
			chdir(arg);
		}
		else
		{
			if (chdir(arg) < 0)
			{
				perror("cd");
				return (-1);
			}
			setenv("OLDPWD", getcwd(NULL, 0), 1);
		}
		return (0);
	}
	return (-1);
}
