#ifndef MAIN_H
#define MAIN_H

#include <sys/stat.h>


/* Function declarations */
int command_exists(char *cmd);
int find_command_in_path(char *cmd, char *fullpath);
void handle_cat(char *filename);
void handle_echo(char **argv);

#endif /* MAIN.H */


