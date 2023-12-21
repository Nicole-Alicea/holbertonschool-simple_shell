#include "main.h"
#include <ctype.h>

void hsh_cat(char *, char *);
void hsh_cd(char *, char *);
void hsh_exit(char *, char *, char *);
/**
 * main - prompt shell
 * Description: function that prompts user for command.
 * Return: 0
 */
int main(void)
{
	char *command = NULL, *cmd, *arg, *start, *end;
	size_t len = 0;
	ssize_t nread;
	int is_interactive;

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
		hsh_exit(cmd, arg, command);
		execute_command(cmd, arg);
	}
	free(command);
	return (0);
}
/**
 * hsh_cat - cat command
 * Description: function that cats
 * @cmdd: cmd
 * @argg: arg
 */
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
/**
 * hsh_cd - change dir
 * Description: function to cd command
 * @cmdd: cmd
 * @argg: arg
 */
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
/**
 * hsh_exit - exit loop
 * Description: function that evals
 * @cmdd: cmd
 * @argg: arg
 * @commandd: command
 */
void hsh_exit(char *cmdd, char *argg, char *commandd)
{
	int i;

	if (strcmp(cmdd, "exit") == 0)
	{
		free(commandd);
		exit(0);
		chdir(argg);
		setenv("OLDPWD", getcwd(NULL, 0), 1);
		return;
	}
	if (strcmp(cmdd, "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			printf("%s\n", environ[i]);
		}
		exit(2);
	}
	if (strcmp(cmdd, "exit") == 0)
	{
		free(commandd);
		exit(0);
		return;
	}
}
