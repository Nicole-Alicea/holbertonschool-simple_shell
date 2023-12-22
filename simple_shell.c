#include "main.h"

/**
 * process_input - Processes the input command, extracts the command and
 * argument, and performs the corresponding action
 * @command: Input command string to be processed
 *
 * Return: 0 if "exit" command is called, 1 otherwise
 */

int process_input(char *command)
{
	char *cmd = strtok(command, " ");
	char *arg = strtok(NULL, " ");

	if (cmd)
	{
		if (strcmp(cmd, "cat") == 0)
		{
			handle_cat(arg);
		}
		else if (strcmp(cmd, "cd") == 0)
		{
			handle_cd(arg);
		}
		else if (strcmp(cmd, "env") == 0)
		{
			handle_env(arg);
		}
		else if (strcmp(cmd, "exit") == 0)
		{
			handle_exit(arg); /*pass the argument to handle_exit*/
			return (0); /*indicates "exit" command was processed*/
		}
		else
		{
			execute_command(cmd, arg);
		}
	}
	return (1);/*indicates a command other than "exit" was processed*/
}

/**
 * main - entry point
 * Description: Prompts user for command
 * Return: 0
 */

int main(void)
{
	char *command = NULL, *start, *end;
	size_t len = 0;
	ssize_t nread;
	int is_interactive;

	is_interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (is_interactive)
			printf("simple_shell_NJR($) ");

		nread = getline(&command, &len, stdin);
		if (nread == -1)
		{
			if (is_interactive)
				printf("\n");
			break;
		}
		start = command;
		end = command + strlen(command) - 1;

		while (*start && isspace((unsigned char)*start))
			start++;
		while (end > start && isspace((unsigned char)*end))
			end--;
		*(end + 1) = '\0';
		if (*start != '\0')
		{
			if (process_input(start) == 0)
			{
				break;
			}
		}
	}
	free(command);
	return (0);
}
