#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <ctype.h>

extern char **environ;

#define MAX_COMMAND_LENGTH 100
/*
 * interactive mode definitions here
 **/
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define MAX_ARGS 64
#define MAX_PATH_LENGTH 1024
#define MAX_INPUT_SIZE 1024

extern char **environ;
/* Function declarations */
int command_exists(char *cmd);
int find_command_in_path(char *cmd, char *fullpath);
void handle_cat(char *filename);
int is_path(char *cmd);
int handle_cd(char *path);
void execute_command(char *cmd, char *arg);
void handle_env(char *cmd);
void handle_exit(char *arg);

#endif /* MAIN.H */
