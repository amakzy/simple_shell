#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 100

/**
 *struct command - a struct that maps a command name to a function
 * @name: name of the command
 * @args: the function that executes the command
 */
struct command
{
	char *name;
	char **args;
};

/* Built-in command functions*/
void changeDirectory(char **args);
void printEnvVariables(void);
void exitShell(char **args);
extern char **environ;

/*Execute and run commands*/
int executeCommand(struct command *cmd);
int runExternalCommand(struct command *cmd);
int runPipedCommands(struct command *cmd1, struct command *cmd2);

/* Read a command from input */
struct command *readCommand(void);

/* Tokenize a string into arguments */
char **tokenize(char *line);

/*Parse a command string into a struct*/
struct command *parseCommand(char *input);

/* Cleanup memory */
void freeCommand(struct command *cmd);

/* environment handling */
char *getEnvVar(const char *name);
void setEnvVar(const char *name, const char *value);
void unsetEnvVar(const char *name);
int asprintf(char **strp, const char *fmt, ...);
#endif
