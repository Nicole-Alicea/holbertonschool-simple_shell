#include "main.h"

/**
 * main - entry point
 *
 * Return: 0
 */

int main(void)
{
	if (isatty(STDIN_FILENO))
	{
		char *prompt = "Input command: ", *lineptr = NULL;
		size_t n = 0;
		ssize_t read;

		while (1)
		{
			printf("%s", prompt);
			read = getline(&lineptr, &n, stdin);

			if (read != -1)
			{
				printf("%s\n", lineptr);
				free(lineptr);
				lineptr = NULL;
			}
			else if (read == -1)
			{
				printf("End of file\n");
				return (-1);
			}
		}
	}
	else
	{
		return (-1);
	}
	return (0);
}
