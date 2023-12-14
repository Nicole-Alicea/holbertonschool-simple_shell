#include <stdio.h>
#include <unistd.h>

/**
 * main - program that prints the PID of the parent process.
 * Description: function prints the pid of the parent process.
 * Run it then: echo $$ to the console, what happens?
 * Return: sucess
 */

int main(void)
{
	pid_t process_id;
	pid_t parent_process_id;

	process_id = getpid();
	printf("process id: %ld\n", process_id);

	parent_process_id = getppid();
	printf("parent process id: %ld\n", parent_process_id);
	return (0);
}
