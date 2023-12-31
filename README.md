# Simple Shell

### Description

For this simple shell project, we were divided into groups of three and given the task of writing a simple UNIX command interpreter. A Unix shell is a command-line interpreter that provides a command line user interface for Unix-like operating systems. The shell is both an interactive command language and a scripting language, and it is used by the operating system to control the execution of the system using shell scripts.

-----------------------
### Resources

[Unix shell](https://en.wikipedia.org/wiki/Unix_shell)

[Thompson shell](https://en.wikipedia.org/wiki/Thompson_shell)

[Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson)

[Everything you need to know to start coding your own shell](https://intranet.hbtn.io/concepts/900)

-----------------------
## Learning Objectives
### General
- Who designed and implemented the original Unix operating system
- Who wrote the first version of the UNIX shell
- Who invented the B programming language (the direct predecessor to the C programming language)
- Who is Ken Thompson
- How does a shell work
- What is a pid and a ppid
- How to manipulate the environment of the current process
- What is the difference between a function and a system call
- How to create processes
- What are the three prototypes of main
- How does the shell use the PATH to find the programs
- How to execute another program with the execve system call
- How to suspend the execution of a process until one of its children terminates
- What is EOF / “end-of-file”?
---------------------------
## Requirements
### General
- Allowed editors: vi, vim, emacs
- All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
- All your files should end with a new line
- A README.md file, at the root of the folder of the project is mandatory
- Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
- Your shell should not have any memory leaks
- No more than 5 functions per file
- All your header files should be include guarded
- Use system calls only when you need to (why?)
-----------------------------
## More Info
### Output
- Unless specified otherwise, your program must have the exact same output as sh (/bin/sh) as well as the exact same error output.
- The only difference is when you print an error, the name of the program must be equivalent to your argv[0] (See below)

  *Example*
     - #### error with sh:
       
       $ echo "qwerty" | /bin/sh
       
       /bin/sh: 1: qwerty: not found
       
       $ echo "qwerty" | /bin/../bin/sh

       /bin/../bin/sh: 1: qwerty: not found

       $

     - #### same error with your program hsh:

       $ echo "qwerty" | ./hsh

       ./hsh: 1: qwerty: not found

       $ echo "qwerty" | ./././hsh

       ./././hsh: 1: qwerty: not found

       $
-------------------------------

#### List of allowed functions and system calls+

Functions and System Calls+                 |Description
|-----------------------------|----------------------------------------------|
| strlen() | Returns the length of the string. |
| strcpy() | Copy one string to another. |
| strncpy() | Copy first n characters of one string to another. |
| strcat() | Concatenates two strings. |
| strncat() | Concatenates first n characters of one string to another. |
| strcmp() | Compares two strings. |
| strncmp() | Compares first n characters of two strings. |
| strchr() | Find the first occurrence of the given character in the string. |
| strrchr() | Finds the last occurrence of the given characters in the string. |
| strstr() | Find the given substring in the string. |
| strcspn() | Returns the span of the source string not containing any character of the given string. |
| strspn() | Returns the span of the source string containing only the characters of the given string. |
| strpbrk() | Finds the first occurrence of any of the characters of the given string in the source string. |
| strtok() | Split the given string into tokens based on some character as a delimiter. |
| strcoll() | Compares two strings that are passed. |
| memset() | Initialize a block of memory with the given character. |
| memcmp() | Compares two blocks of memory. |
| memcpy() | Copy two blocks of memory. |
| memmove() | Moves two blocks of memory. |
| memchr() | Finds the given character in the block of memory. |
| access (man 2 access) | Checks to see if the file or directory specified by path exists and if it can be accessed with the file access permissions given by amode. |
| chdir (man 2 chdir) | Changes the current working directory to path, which can be relative to the current working directory or an absolute path name. |
| close (man 2 close) | Closes a file descriptor, so that it no longer refers to any file and may be reused.
| closedir (man 3 closedir) | Closes the directory stream associated with dirp. |
| execve (man 2 execve) | Executes the program referred to by pathname. |
| exit (man 3 exit) | Causes normal process termination and the least significant byte of status is returned to the parent. |
| _exit (man 2 _exit) | Terminates the calling process "immediately". |
| fflush (man 3 fflush) | Forces a write of all user-space buffered data for the given output or update stream via the stream's underlying write function. |
| fork (man 2 fork) | Creates a new process by duplicating the calling process. |
| free (man 3 free) | Frees the memory space pointed to by ptr, which must have been returned by a previous call to malloc(), calloc(),  or  realloc(). |
| getcwd (man 3 getcwd) | Copies an absolute pathname of the current working directory to the array pointed to by buf, which is of length size. |
| getline (man 3 getline) | Reads an entire line from stream, storing the address of the buffer containing the text into *lineptr. |
| getpid (man 2 getpid) | Returns the process ID (PID) of the calling process. |
| isatty (man 3 isatty) | Tests whether fd is an open file descriptor referring to a terminal. |
| kill (man 2 kill) | Can be used to send any signal to any process group or process. |
| malloc (man 3 malloc) | Allocates size bytes and returns a pointer to the allocated memory. |
| open (man 2 open) | Opens the file specified by pathname. |
| opendir (man 3 opendir) | Opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream. |
| perror (man 3 perror) | Produces a message on standard error describing the last error encountered during a call to a system or library function. |
| printf (man 3 printf) | Writes output to stdout. |
| fprintf (man 3 fprintf) | Writes output to the given output stream. |
| vfprintf (man 3 vfprintf) | Writes output to the given output stream. |
| sprintf (man 3 sprintf) | writes to the character string str. |
| putchar (man 3 putchar) | Writes a single character to the standard output stream, stdout. |
| read (man 2 read) | Attempts to read up to count bytes from file descriptor fd into the buffer starting at buf. |
| readdir (man 3 readdir) | Returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp. |
| signal (man 2 signal) | Returns the previous value of the signal handler. |
| stat (__xstat) (man 2 stat) | Retrieves information about the file pointed to by pathname. |
| lstat (__lxstat) (man 2 lstat) | Identical to stat(), except that if pathname is a symbolic link, then it returns information about the link  it‐self, not the file that the link refers to. |
| fstat (__fxstat) (man 2 fstat) | Identical to stat(), except that the file about which information is to be retrieved is specified by the file descriptor fd. |
| strtok (man 3 strtok) | Breaks a string into a sequence of zero or more nonempty tokens. |
| wait (man 2 wait) | Suspends execution of the calling thread until one of its children terminates. |
| waitpid (man 2 waitpid) | Suspends execution of the calling thread until a child specified by pid argument has changed state. |
| wait3 (man 2 wait3) | Allows the calling process to obtain status information for specified child processes. |
| wait4 (man 2 wait4) | Suspends execution of the calling thread until status information from one of ots terminated child processes is available, or until the delivery of a signal whose action is either to terminate the process or execute a signal handler. |
| write (man 2 write) | Writes to an open file. |

### Compilation
The program will be compiled this way:

*$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh**

#### List of files contained in this repository

Name           |
|---------------------|
| README.md |
| AUTHORS |
| man_1_simple_shell |
| simple_shell.c |

#### Tasks

--------------------

0. #### README, man, AUTHORS
- Write a README
- Write a man for your shell.
- You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository. Format, see Docker

1. #### Betty would be proud
- Write a beautiful code that passes the Betty checks

2. #### Simple shell 0.1

Write a UNIX command line interpreter.
- Usage: simple_shell
Your Shell should:
- Display a prompt and wait for the user to type a command. A command line always ends with a new line.
- The prompt is displayed again each time a command has been executed.
- The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
- The command lines are made only of one word. No arguments will be passed to programs.
- If an executable cannot be found, print an error message and display the prompt again.
- Handle errors.
- You have to handle the “end of file” condition (Ctrl+D)

You don’t have to:
- use the PATH
- implement built-ins
- handle special characters : ", ', `, \, *, &, #
- be able to move the cursor
- handle commands with arguments
*execve will be the core part of your Shell, don’t forget to pass the environ to it…**

3. #### Simple shell 0.2
Simple shell 0.1 +
- Handle command lines with arguments

4. #### Simple shell 0.3
Simple shell 0.2 +
- Handle the PATH
- fork must not be called if the command doesn’t exist

5. #### Simple shell 0.4
Simple shell 0.3 +
- Implement the exit built-in, that exits the shell
- Usage: exit
- You don’t have to handle any argument to the built-in exit

6. #### Simple shell 1.0
Simple shell 0.4 +
- Implement the env built-in, that prints the current environment

7. #### What happens when you type `ls -l *.c` in the shell
Write a blog post describing step by step what happens when you type ls -l *.c and hit Enter in a shell. Try to explain every step you know of, going in as much details as you can, give examples and draw diagrams when needed. You should merge your previous knowledge of the shell with the specifics of how it works under the hoods (including syscalls).
- Have at least one picture, at the top of the blog post
- Publish your blog post on Medium or LinkedIn
- Share your blog post at least on LinkedIn
- Only one blog post by team
- The blog post must be done and published before the first deadline (it will be part of the manual review)
- Please, remember that these blogs must be written in English to further your technical ability in a variety of settings

8. #### Test suite
Contribute to a test suite for your shell.

This is a task shared by everyone in the class.
- Every team (who contributed) will get the same score for this task (The repository owner will not get more points)
- You have to be pro-active and agree on one and unique repository to use for the test suite
- Please provide the link to the repository you contributed to
- Your contribution must be relevant (Correcting typos is nice and always appreciated on the open source sphere, but we won’t consider this a contribution at this point, unless it fixes a bug)
Guidelines for your test suite repository:
- The test suite should cover every tasks from 0. to 20.
- The test suite should cover every regular cases (many different examples) and possible edge cases
- The entire class should work on the same test suite. Use only one repository (don’t forget the README.md file)
- Start adding tests ASAP and not just before the deadline in order to help everyone from day 0
- You can take (or fork) inspiration from this example, but it is not mandatory to follow this format/way
- Adopt a style and be consistent. You can, for example, follow this style guide. If you choose a style that already exists, add it to the README.md in a style section. If you write your own, create a Wiki page attached to the project and refer to it in the README.md style section.
  - If you choose to use this code, make sure to update the style accordingly
- You should have an AUTHORS file, listing all individuals having contributed content to the repository. Format, see Docker

9. #### Simple shell 0.1.1
Simple shell 0.1 +
- Write your own getline function
- Use a buffer to read many chars at once and call the least possible the read system call
- You will need to use static variables
- You are not allowed to use getline
You don’t have to:
- be able to move the cursor

10. #### Simple shell 0.2.1
Simple shell 0.2 +
- You are not allowed to use strtok

11. #### Simple shell 0.4.1
Simple shell 0.4 +
- handle arguments for the built-in exit
- Usage: exit status, where status is an integer used to exit the shell

12. #### Simple shell 0.4.2
Simple shell 0.4 +
- Handle Ctrl+C: your shell should not quit when the user inputs ^C
man 2 signal.

13. #### setenv, unsetenv
Simple shell 1.0 +
Implement the setenv and unsetenv builtin commands
- setenv
  - Initialize a new environment variable, or modify an existing one
  - Command syntax: setenv VARIABLE VALUE
  - Should print something on stderr on failure
- unsetenv
  - Remove an environment variable
  - Command syntax: unsetenv VARIABLE
  - Should print something on stderr on failure

14. #### cd
Simple shell 1.0 +
Implement the builtin command cd:
- Changes the current directory of the process.
- Command syntax: cd [DIRECTORY]
- If no argument is given to cd the command must be interpreted like cd $HOME
- You have to handle the command cd -
- You have to update the environment variable PWD when you change directory
man chdir, man getcwd

15. #### ;
Simple shell 1.0 +
- Handle the commands separator ;

16. #### && and ||
Simple shell 1.0 +
- Handle the && and || shell logical operators

17. #### alias
Simple shell 1.0 +
- Implement the alias builtin command
- Usage: alias [name[='value'] ...]
  - alias: Prints a list of all aliases, one per line, in the form name='value'
  - alias name [name2 ...]: Prints the aliases name, name2, etc 1 per line, in the form name='value'
  - alias name='value' [...]: Defines an alias for each name whose value is given. If name is already an alias, replaces its value with value
 
18. #### Variables
Simple shell 1.0 +
- Handle variables replacement
- Handle the $? variable
- Handle the $$ variable

19. #### Comments
Simple shell 1.0 +
- Handle comments (#)

20. #### help
Simple shell 1.0 +
- Implement the help built-in
- Usage: help [BUILTIN]

21. #### history
Simple shell 1.0 +
- Implement the history built-in, without any argument
- The history built-in displays the history list, one command by line, preceded with line numbers (starting at 0)
- On exit, write the entire history, without line numbers, to a file named .simple_shell_history in the directory $HOME
- When the shell starts, read the file .simple_shell_history in the directory $HOME if it exists, and set the first line number to the total number of lines in the file modulo 4096

22. #### File as input
Simple shell 1.0 +
- Usage: simple_shell [filename]
- Your shell can take a file as a command line argument
- The file contains all the commands that your shell should run before exiting
- The file should contain one command per line
- In this mode, the shell should not print a prompt and should not read from stdin

### Authors &copy;

- Jeremy Cardona Crespo
- Nicole Alicea Plumey
- Raphael Santos
