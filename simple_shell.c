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
		char *prompt = "Input command: ", *lineptr;
		size_t n = 0;

		printf("%s", prompt);
		getline(&lineptr, &n, stdin);
		printf("%s\n", lineptr);
		free(lineptr);
	}
	else
	{
		return (-1);
	}
	return (0);
}
