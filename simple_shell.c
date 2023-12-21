#include "main.h"
#include <ctype.h>

/**
 * main - entry point
 *
 * Return: 0
 */

int main(void)
{
	char *command = NULL, *cmd, *arg, *start, *end;
	size_t len = 0;
	ssize_t nread;
	int is_interactive, i;

	is_interactive = isatty(STDIN_FILENO);

	while (1) 
	{
		if (is_interactive)
		{
			printf("simple_shell_NJR($) ");
		}

		nread = getline(&command, &len, stdin);
		if (nread == -1)
		{
			if (is_interactive)
			{
				printf("\n");
			}
			break;
		}
		start = command;
		end = command + strlen(command) - 1;

		while (*start && isspace((unsigned char)*start))
			start++;
		while (end > start && isspace((unsigned char)*end))
			end--;
		*(end + 1) = '\0';
		if (*start == '\0')
		{
			continue;
		}
		
		cmd = strtok(start, " ");
		arg = strtok(NULL, " ");
		
		if (cmd && strcmp(cmd, "cat") == 0)
		{
			if (arg == NULL)
			{
				fprintf(stderr, "cat: Missing file name\n");
			}
			else
			{
				handle_cat(arg);
			}
			continue;
		}
		if (strcmp(cmd, "cd") == 0)
		{
			if (arg == NULL || strcmp(arg, "~") == 0 || strcmp(arg, "$HOME") == 0)
			{
				chdir(getenv("HOME"));
				continue;
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
				continue;
			}
			else if (strcmp(arg, "/tmp") == 0)
			{
				chdir(arg);
				continue;
			}
			else
			{
				if (cd(arg) < 0)
				{
					perror("cd");
					continue;
				}

				chdir(arg);
				setenv("OLDPWD", getcwd(NULL, 0), 1);
				continue;
			}
		}
		if (strcmp(cmd, "env") == 0)
		{
			for (i = 0; environ[i] != NULL; i++)
			{
				printf("%s\n", environ[i]);
			}
			continue;
		}
		if (strcmp(cmd, "exit") == 0)
		{
			free(command);
			return (0);
		}
		execute_command(cmd, arg);
	}
	free(command);
	return (0);
}
