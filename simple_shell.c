#include "main.h"

/* Check if a command exists at the given path */
int command_exists(char *cmd)
{
	struct stat st;
	return (stat(cmd, &st) == 0);
}

/** 
 * find_command_in_path - find command in current path
 * Description: find the path to 
 * Find a command in the directories specified by the PATH environment variable */

int find_command_in_path(char *cmd, char *fullpath)
{
	struct stat st;
	char *path, *token, pth[MAX_PATH_LENGTH];

	/* Check if cmd is an absolute path */
	if (cmd[0] == '/')
	{
		if (stat(cmd, &st) == 0)
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
			if (stat(fullpath, &st) == 0)
			{
				return (1); /* Command found */
			}
			token = strtok(NULL, ":");
		}
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

int main()
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
		/* Continue if command is empty */
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
		/* Split the command into arguments */
		argc = 0;
		argv[argc] = strtok(command, " ");
		while (argv[argc] != NULL && argc < MAX_ARGS - 1)
		{
			argv[++argc] = strtok(NULL, " ");
		}
		argv[argc] = NULL;
		
		/* Handle 'cat' command */
		if (strcmp(argv[0], "cat") == 0 && argv[1] != NULL)
		{
			handle_cat(argv[1]);
			continue;
		}
		/* Check if the command exists in PATH */
		if (!find_command_in_path(argv[0], fullpath))
		{
			printf("%s: command not found\n", argv[0]);
			continue;
		}
		
		/* Fork a new process to execute the command */
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}
		if (pid == 0)
		{
			/* Child process */
			execv(fullpath, argv); /* Execute the command */
			perror("execv"); /* Executed only if execv fails */
			exit(2);
		}
		else
		{
			/* Parent process */
			wait(NULL); /* Wait for the child process to finish */
		}
	}
	free(command);
	return (0);
}
