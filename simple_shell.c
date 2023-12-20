#include "main.h"

/**
 * main - entry point, serving as the starting point
 * for the execution of the shell program 
 *
 * Return: 0 (Success)
 */

int main(int argcount, char **argvector)
{
	char *command = NULL, *argv[MAX_ARGS], fullpath[MAX_PATH_LENGTH];
	size_t len = 0;
	ssize_t nread;
	int is_interactive = isatty(STDIN_FILENO), argc;
	pid_t pid;
	
	while (1)
	{
		/* Display the prompt only in interactive mode */
		if (is_interactive)
		{
			printf(ANSI_COLOR_RED ANSI_COLOR_RESET);
			printf("simple_shell_NJR($) ");
		}
		else
		{
			printf("%s ", argvector[0]);
		}
		/* Read a line of input using getline */
		nread = getline(&command, &len, stdin);
		if (nread == -1)
		{
			if (is_interactive)
			{
				printf("\n");
			}
			break; /* Exit on EOF or read error */
		}
		/* Remove newline character from the end of the command */
		if (command[nread - 1] == '\n')
		{
			command[nread - 1] = '\0';
		}
		/* Continue if command is empty or NULL */
		if (strlen(command) == 0)
		{
			continue;
		}
		/* Exit the shell if the command is 'exit' */
		if (strcmp(command, "exit") == 0)
		{
			free(command);
			exit(0);
		}
		if (command == NULL)
		{
			continue;
		}
		/* Split the command into arguments */
		argc = 0;
		argv[argc] = strtok(command, " ");
		while (argv[argc] != NULL && argc < MAX_ARGS - 1)
		{
			argv[++argc] = strtok(NULL, " ");
		}
		/* argcount instead of argc! */
		argv[argcount] = NULL;
		
		/* Handle 'cat' command */
		if (strcmp(argv[0], "cat") == 0 && argv[1] != NULL)
		{
			handle_cat(argv[1]);
			continue;
		}
		/* Check if the command exists in PATH */
		if (argv[0] == NULL || !find_command_in_path(argv[0], fullpath))
		{
			fprintf(stderr, "Command not found or empty command\n");
			continue;
		}
		
		/* Fork a new process to execute the command */
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}
		/* Child process - pid == 0 */
		dup2(STDOUT_FILENO, STDERR_FILENO); /*This redirects the stderr to stdout*/
		execvp(argv[0], argv); /* Execute the command */
		perror("execvp"); /* Executed only if execv fails */
		exit(2);

		/*
		else
		if (pid == 0) [if it equals 0, it's the child process]
		{
			[ We write here what we want the Child process to do ]
			dup2(STDOUT_FILENO, STDERR_FILENO); [This redirects the stderr to stdout]
			execvp(argv[0], argv); [Execute the command]
			perror("execvp"); [Executed only if execv fails]
			exit(2);
		}
		else [This is for the parent process. It returns a positive integer greater than 0]
		{
			[We write here what we want the parent process to do]
			int status;
			waitpid(pid, &status, 0);

			if (WIFEXITED(status))
			{
				if (WEXITSTATUS(status) != 0)
				{
					fprintf(stderr, "Command failed with status %d\n", WEXITSTATUS(status));
				}
			}
		}
		*/
	}
	free(command);
	return (0);
}
