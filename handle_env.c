#include "main.h"


void handle_env(char *cmd)
{
	int i;

	if (strcmp(cmd, "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			printf("%s\n", environ[i]);
		}
	}
}
