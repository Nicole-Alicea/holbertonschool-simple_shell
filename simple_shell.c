#include "main.h"

/* Check if a command exists at the given path */
int command_exists(char *cmd)
{
	struct stat st;
	return (stat(cmd, &st) == 0);
}

/** 
 * find_command_in_path - find command in current path
 * Description: function that finds the command in current path.
 * Find a command in the directories specified by the PATH environment variable
 * @cmd: command
 * @fullpath: fullpath
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
				return (1);
			}
		}
		token = strtok(NULL, ":");
	}
	return (0); /* Command not found */
}


/* Handle the 'cat' command */
void handle_cat(char *filename)
{
	char line[1024];
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		perror("fopen");
		return;
	}
	while (fgets(line, sizeof(line), file) != NULL)
	{
		printf("%s", line);
	}
	fclose(file);
}

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
		/* if (pid == 0) 
		{ */
		/* Child process */
		dup2(STDOUT_FILENO, STDERR_FILENO); /*This redirects the stderr to stdout*/
		execvp(argv[0], argv); /* Execute the command */
		perror("execvp"); /* Executed only if execv fails */
		exit(2);
		/* } */
		/*
		else
		{
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
