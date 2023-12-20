#include <stdio.h>

/**
 * main - print all the argv
 * Description: program that prints all the argument vector
 * of the main function without using the argument count param.
 * Return: argc
 * @argc: argument count
 * @argv: argument vector
 */

int main (int argc, char **argv)
{	
	while (*(++argv))
		printf("%s\n", (*(argv)));
	
	return (argc);
}
