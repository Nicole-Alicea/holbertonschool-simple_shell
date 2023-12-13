#include "main.h"

/**
 * main - entry point
 *
 * Return: 0
 */

extern char **environ; /*code wouldn't compile unless I declared environ as an external char. I'm looking for another way to handle the env built in*/

int main(void) /*I'm thinking we might have to put argc and argv*/
{
	if (isatty(STDIN_FILENO)) /*This checks if file descriptor refers to a terminal(shell is running in interactive mode)*/
	{
		char *prompt = "Input command: ", *lineptr = NULL;
		size_t n = 0;
		ssize_t read;

		while (1) /*This creates an infinite loop so that a prompt will keep appearing after a command has been executed.*/
		{
			printf("%s", prompt); /*prints the prompt*/
			read = getline(&lineptr, &n, stdin); /*reads the user input*/

			if (read != -1) /*checks if the input is not EOF*/
			{
				if (strcmp(lineptr, "env\n") == 0)
				{
					char **env = environ;
					while (*env != NULL)
					{
						printf("%s\n", *env); /*iterates through environ and prints each one*/
						env++;
					}
				}
				else
				{
					printf("%s", lineptr);
				}
				free(lineptr); /*frees the memory allocated for the user input*/
				lineptr = NULL; /*this is here to deal with the core dump error I kept getting. It resets the pointer to NUll after freeing memory.*/
			}
			else /*reaches EOF*/
			{
				printf("End of file\n");
				free(lineptr);
				return (0);
			}
		}
	}
	else
	{
		return (-1);
	}
	return (0);
}
