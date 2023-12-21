#include "main.h"

void execute_command(char *cmd, char *arg)
{
	char *argv[3], fullpath[MAX_PATH_LENGTH];
	int status, exit_status;
	pid_t pid = fork();

	if (is_path(cmd))
		strcpy(fullpath, cmd);
	else if (!find_command_in_path(cmd, fullpath))
	{
		fprintf(stderr, "Command not found: %s\n", cmd);
		return;
	}

	if (pid == 0)
	{
		argv[0] = fullpath;
		argv[1] = arg;
		argv[2] = NULL;
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
				fprintf(stderr, "Command exited with non-zero status: %d\n", exit_status);
		}
	}
	else
		perror("fork");
}
