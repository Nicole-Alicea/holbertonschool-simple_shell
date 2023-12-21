#include "main.h"

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
		handle_cd(cmd);
		handle_env(cmd);
		handle_exit(cmd);
		execute_command(cmd, arg);
	}
	free(command);
	return (0);
}
