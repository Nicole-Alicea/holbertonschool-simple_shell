#include "main.h"

/**
 * handle_cat - This function reads and prints the contents of a file
 * @filename: pointer to the file to be read
 *
 * Return: void
 */

void handle_cat(char *filename)
{
	char line[1024], *cmd, *arg, *start, *command = NULL;
	FILE *file = fopen(filename, "r");

	start = command;
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
	}
}
