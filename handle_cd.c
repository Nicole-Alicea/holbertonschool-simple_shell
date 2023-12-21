#include "main.h"

/**
 * cd - This function will handle "cd"
 * @path: The path to which you want to change the current working directory
 *
 * Return: 0 Success or -1 upon a failure
 */

int cd(char *path)
{
	return (chdir(path));
}
