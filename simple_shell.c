#include "main.h"
#include <ctype.h>

/**
 * main - prompt shell
 * Description: function that prompts user for command.
 * Return: 0
 */

void hsh_cat(char *, char *);
void hsh_cd(char *, char *);
void hsh_exit(void);


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

		hsh_cat(cmd, arg);
		hsh_cd(cmd, arg);
		if (strcmp(cmd, "exit") == 0)
		{
			free(command);
			exit(0);
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

void hsh_cat(char *cmdd, char *argg)
{
	if (*cmdd && strcmp(cmdd, "cat") == 0)
	{
		if (argg == NULL)
		{
			fprintf(stderr, "cat: Missing file name\n");
		}
		else
		{
			handle_cat(argg);
		}
		return;
	}
}
void hsh_cd(char *cmdd, char *argg)
{
	char *oldpwd;

	if (strcmp(cmdd, "cd") == 0)
	{
		if (argg == NULL || strcmp(argg, "~") == 0 || strcmp(argg, "$HOME") == 0)
		{
			chdir(getenv("HOME"));
			return;
		}
		else if (strcmp(argg, "-") == 0)
		{
			oldpwd = getenv("OLDPWD");
			if (oldpwd != NULL)
			{
				chdir(oldpwd);
				printf("%s\n", oldpwd);
			}
			else
			{
				fprintf(stderr, "OLDPWD not set\n");
			}
			return;
		}
		else if (strcmp(argg, "/tmp") == 0)
		{
			chdir(argg);
			return;
		}
		else
		{
			if (cd(argg) < 0)
			{
				perror("cd");
				return;
			}

			chdir(argg);
			setenv("OLDPWD", getcwd(NULL, 0), 1);
			return;
		}
	}
}
void hsh_exit(void)
{
	return;
}
