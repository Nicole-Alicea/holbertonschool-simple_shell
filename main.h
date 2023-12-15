#ifndef MAIN_H
#define MAIN_H

/*
 * interactive mode definitions here
 **/
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define MAX_ARGS 10
#define MAX_PATH_LENGTH 1024

/* Function declarations */
int command_exists(char *cmd);
int find_command_in_path(char *cmd, char *fullpath);
void handle_cat(char *filename);
void handle_echo(char **argv);

#endif /* MAIN.H */
