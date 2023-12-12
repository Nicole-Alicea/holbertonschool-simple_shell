#include "main.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0
 */

int main(int argc, char **argv)
{
	char *prompt = "Input command:", *token;
	char *lineptr = NULL, *lineptr_copy = NULL;
	size_t n = 0;
	ssize_t chars_read;
	const char *delimiter = " \n";
	int num_tokens = 0, m;

	(void)argc;

	while (1)
	{
		printf("%s", prompt);
		chars_read = getline(&lineptr, &n, stdin);

		if (chars_read == -1)
		{
			printf("End of file\n");
			return (-1);
		}
		
		lineptr_copy = malloc(sizeof(char) * chars_read);

		if (lineptr_copy == NULL)
		{
			perror("Memory allocation failed");
			return (-1);
		}
		strcpy(lineptr_copy, lineptr);
		token = strtok(lineptr, delimiter);

		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, delimiter);
		}
		num_tokens++;

		argv = malloc(sizeof(char *) * num_tokens);

		token = strtok(lineptr_copy, delimiter);

		for (m = 0; token != NULL; m++)
		{
			argv[m] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[m], token);

			token = strtok(NULL, delimiter);
		}
		argv[m] = NULL;

		printf("%s\n", lineptr);
		
		free(lineptr);
	}
	return (0);
}
