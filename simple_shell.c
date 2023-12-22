#include "main.h"

void print_prompt(int is_interactive)
{
	if (is_interactive)
	{
		printf("simple_shell_NJR($) ");
	}
}

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

int execute_command(char *cmd, char *arg, char *fullpath)
{
	pid_t pid;
	int status, exit_status;
	(void)cmd;

	pid = fork();
	if (pid == 0)
	{
		char **argv = malloc(sizeof(char *) * 3);

		if (argv == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		argv[0] = fullpath;
		argv[1] = arg;
		argv[2] = NULL;

		execve(fullpath, argv, environ);
		perror("execve");
		free(argv);
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

void process_input(char *command, int is_interactive)
{
	char *cmd, *arg, *start, *end, fullpath[MAX_PATH_LENGTH];
	int i, result;
	(void)is_interactive;

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
		{
			printf("%s\n", environ[i]);
		}
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
		process_input(command, is_interactive);

		if (strcmp(strtok(command, " "), "exit") == 0)
		{
			free(command);
			exit(0);
		}
	}
	free(command);
	return (0);
}
