#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 100
#define MAX_NUM_DIRS 10

/**
 * changeDirectory - built-in command functions
 * @args: argument passed to command
*/
void changeDirectory(char **args);
void printEnvVariables(void);
void exitShell(char **args);

/**
 * execArgs - executes commands
 * @args: parsed input arguments
*/
void execArgs(char **args);

/**
 * parseInput - parses input into tokens
 * @input: input string to parse
 * Return: array of input
*/
char **parseInput(char *input);

/**
 * readInput - reads input from stdin
 *
 * Return: input string
*/
char *readInput();

/**
 * main - shell main function
 *
 * runs in a loop to accept user input, parse it, and execute commands.
 * Return: 0
*/
int main(void)
{
	char *input;
	char **args;

	while (1)
	{
		/* Print prompt */
		printf("> ");

		/* Read input */
		input = readInput();

		/* Parse input into tokens */
		args = parseInput(input);

		/* Execute command */
		execArgs(args);

		/* Free parsed input */
		free(input);
		free(args);
	}

}

/**
 * execArgs - executes commands
 *
 * @args: parsed input argument
 *
 * Return: data
*/
void execArgs(char **args)
{
	/* Built-in commands */
	if (strcmp(args[0], "cd") == 0)
	{
		changeDirectory(args);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		printEnvVariables();
	}
	else if (strcmp(args[0], "exit") == 0)
	{
		exitShell(args);
	}
	else
	{
		/* Fork and execute command */
		pid_t pid = fork();

		if (pid == 0)
		{
			execvp(args[0], args);
			exit(EXIT_FAILURE);
		}
		/* Wait for child process */
		wait(NULL);
	}
}

/* Built-in functions implementations here */

/**
 * readInput - Read input from stdin
 *
 * Return: array of tokens
*/
char *readInput()
{
	char *input = malloc(MAX_INPUT_SIZE);

	fgets(input, MAX_INPUT_SIZE, stdin);

	return (input);

}

/**
 * parseInput - tokenize input string into arguments
 *
 * @input: input string param
 * Return: array of tokens strings
*/
char **parseInput(char *input)
{
	int bufSize = MAX_TOKENS;
	int pos = 0;
	char **tokens = malloc(bufSize * sizeof(char *));
	char *token;

	token = strtok(input, " \t\r\n\a");

	while (token != NULL)
	{
		tokens[pos] = token;
		pos++;

		if (pos >= bufSize)
		{
			bufSize += MAX_TOKENS;
			tokens = realloc(tokens, bufSize * sizeof(char *));
		}

		token = strtok(NULL, " \t\r\n\a");
	}

	tokens[pos] = NULL;
	return (tokens);
}
