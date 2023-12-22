#include "main.h"

/**
 * handle_cat - This function reads and prints the contents of a file
 * @filename: pointer to the file to be read
 *
 * Return: void
 */

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
