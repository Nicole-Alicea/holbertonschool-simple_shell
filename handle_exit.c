#include "main.h"

int handle_exit(char *cmd)
{
	if (strcmp(cmd, "exit") == 0)
	{
		free(cmd);
		return (0);
	}
	return (1);
}
