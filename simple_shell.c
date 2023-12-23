#include "main.h"
/**
 * print_prompt - Prints the shell prompt if the shell
 * is running in interactive mode
 * @is_interactive: Integer flag indicating whether the shell is
 * running in interactive mode
 *
 * Return: void
 */
void print_prompt(int is_interactive)
{
	if (is_interactive)
	{
		printf("simple_shell_NJR($) ");
	}
}

/**
 * trim_whitespace - Trims leading and trailing whitespaces from a string
 * @start: Pointer to the start of the string
 * @end: Pointer to the end of the string
 *
 * Return: void
 */

void trim_whitespace(char **start, char **end)
{
	while (*start && isspace((unsigned char)**start))
	{
		(*start)++;
	}
	while (*end > *start && isspace((unsigned char)**end))
	{
		(*end)--;
	}
	*((*end) + 1) = '\0';
}

/**
 * execute_command - Executes a command with arguments in a
 * child process using 'fork' and 'execve'
 * @cmd: Command to be executed
 * @arg: Argument for the command
 * @fullpath: Full path to the command executable
 *
 * Return: Exit status of the command
 */

int execute_command(char *cmd, char *arg, char *fullpath)
{
	pid_t pid;
	int status, exit_status;
	(void)cmd;

	pid = fork();
	if (pid == 0)
	{
		char *argv[] = {fullpath, arg, NULL;

		execve(fullpath, argv, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			if (exit_status != 0)
			{
				return (exit_status);
			}
		}
	}
	else
	{
		perror("fork");
	}
	return (0);
}

/**
 * process_input - Processes user input by tokenizing the command and
 * performing the corresponding action
 * @command: String containing the user input
 *
 * Return: void
 */

void process_input(char *command)
{
	char *cmd, *arg, *start, *end, fullpath[MAX_PATH_LENGTH];
	int i, result;

	start = command;
	end = command + strlen(command) - 1;

	trim_whitespace(&start, &end);
	if (*start == '\0')
		return;
	cmd = strtok(start, " ");
	arg = strtok(NULL, " ");

	if (cmd && strcmp(cmd, "cat") == 0)
	{
		if (arg == NULL)
			fprintf(stderr, "cat: Missing file name\n");
		else
			handle_cat(arg);
	}
	else if (strcmp(cmd, "exit") == 0)
	{
		free(command);
		exit(0);
	}
	else if (strcmp(cmd, "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);
	}
	else if (is_path(cmd) || find_command_in_path(cmd, fullpath))
	{
		result = execute_command(cmd, arg, fullpath);
		if (result != 0)
		{
			free(command);
			exit(result);
		}
	}
	else
		fprintf(stderr, "Command not found: %s\n", cmd);
}

/**
 * main - Initializaes variables, reads user input in a loop, and processes
 * each input using the 'process_input' function
 *
 * Return: 0 Success
 */
int main(void)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t nread;
	int is_interactive;

	is_interactive = isatty(STDIN_FILENO);
	while (1)
	{
		print_prompt(is_interactive);

		nread = getline(&command, &len, stdin);
		if (nread == -1)
		{
			if (is_interactive)
			{
				printf("\n");
			}
			break;
		}
		process_input(command);

		if (strcmp(strtok(command, " "), "exit") == 0)
		{
			free(command);
			exit(0);
		}
	}
	free(command);
	return (0);
}
