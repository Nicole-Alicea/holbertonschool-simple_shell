# **READ ME!** 
## Concept: everything you need to know to start coding your own shell!
======================
## PID & PPID
- process id and parent process id

-Each process has a parent: the process that created it.
-It is possible to get the PID of a parent process by using the getppid system call, from within the child process.

- for more info: 
man getppid
man getpid

### Exercises - PID, PPID
0. getppid [getppid.c](./0-getppid.c)
- Write a program that prints the PID of the parent process.
- Run your program several times within the same shell. It should be the same. 
- Does echo $$ print the same value? Why?
1. /proc/sys/kernel/pid\_max [print max id value](./max_process.sh)
- write a shell script that prints the maximum value a process ID can be.

--------------------------
## Arguments
- The command line arguments are passed through the main function: int main(int ac, char /*/*av);
* av is a NULL terminated array of strings
* ac is the number of items in av
- av[0] usually contains the name used to invoke the current program. av[1] is the first argument of the program, av[2] the second, and so on.
### Exercises - Arguments
0. av
- Write a program that prints all the arguments, without using ac.
1. read line
* Write a program that prints "$ ", wait for the user to enter a command, prints it on the next line.
* _man getline_
* ` advanced: wrtie your own version of getline. `
2. command line to av
- Write a function that splits a string and returns an array of each word of the string.
- _man strtok_
- ` advanced. write the function without strtok`
---------------------------
## Execute
## Create
## Wait
### Exercises - Executing a program, creating processes and wait.
- Write a program that executes the command ls -l /tmp in 5 different child processes. 
- Each child should be created by the same process (the father).
- Wait for a child to exit before creating a new child.

--------------------------------
### Exercise - Super simple shell
---------------------------------
### Exercise - find a file in the PATH
-----------------------------------
## Environment
### Exercise - Environment

-------------------------
