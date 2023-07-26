#include "shell.h"

/**
 * hash_command - Sets the hash table data
 * Description:
 * the extended functions for main.c
 */

/* Internal command hash table */
static const struct
{
	char *command_name;
	void (*func)(char **command);
}
internal_commands[] = {
	{"env", env},
	{"exit", quit},
	{NULL, NULL}
};

/* Hash function for internal command lookup */
static unsigned int hash_command(const char *command)
{
	unsigned int hash = 5381;
	int c;

	while ((c = *command++))
		hash = ((hash << 5) + hash) + c;
	return (hash);
}

/**
 * parse_command - Determines the type of the command
 * @command: command to be parsed
 *
 * Return: constant representing the type of the command
 * Description -
 *		EXTERNAL_COMMAND (1) represents commands like /bin/ls
 *		INTERNAL_COMMAND (2) represents commands like exit, env
 *		PATH_COMMAND (3) represents commands found in the PATH like ls
 *		INVALID_COMMAND (-1) represents invalid commands
 */
int parse_command(char *command)
{
	int i;
	char *path = NULL;

	for (i = 0; command[i] != '\0'; i++)
	{
		if (command[i] == '/')
			return (EXTERNAL_COMMAND);
	}

	for (i = 0; internal_commands[i].command_name != NULL; i++)
	{
		if (_strcmp(command, internal_commands[i].command_name) == 0)
			return (INTERNAL_COMMAND);
	}

	path = check_path(command);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
}

/**
 * execute_command - executes a command based on its type
 * @tokenized_command: tokenized form of the command (ls -l == {ls, -l, NULL})
 * @command_type: type of the command
 *
 * Return: void
 */
void execute_command(char **tokenized_command, int command_type)
{
	void (*func)(char **command);
	char *path = NULL;

	switch (command_type)
	{
		case EXTERNAL_COMMAND:
			if (execve(tokenized_command[0], tokenized_command, NULL) == -1)
			{
				perror(_getenv("PWD"));
				exit(2);
			}
			break;
		case PATH_COMMAND:
			path = check_path(tokenized_command[0]);
			if (path != NULL)
			{
				if (execve(path, tokenized_command, NULL) == -1)
				{
					perror(_getenv("PWD"));
					exit(2);
				}
				free(path);
			}
			break;
		case INTERNAL_COMMAND:
			func = get_func(tokenized_command[0]);
			if (func != NULL)
				func(tokenized_command);
			break;
		case INVALID_COMMAND:
			print(shell_name, STDERR_FILENO);
			print(": 1: ", STDERR_FILENO);
			print(tokenized_command[0], STDERR_FILENO);
			print(": not found\n", STDERR_FILENO);
			status = 127;
			break;
	}
}

/**
 * check_path - checks if a command is found in the PATH
 * @command: command to be used
 *
 * Return: path where the command is found in, NULL if not found
 */
char *check_path(char *command)
{
	char *path = _getenv("PATH");
	char *token, *path_cpy;
	char *full_path = NULL;

	if (path == NULL || _strlen(path) == 0)
		return (NULL);

	path_cpy = strdup(path);
	token = strtok(path_cpy, ":");

	while (token != NULL)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			exit(2);
		}
		sprintf(full_path, "%s/%s", token, command);
		if (access(full_path, F_OK) == 0)
			break;

		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_cpy);

	return (full_path);
}

/**
 * get_func - retrieves a function based on the command given and a mapping
 * @command: string to check against the mapping
 *
 * Return: pointer to the proper function, or null on fail
 */
void (*get_func(char *command))(char **)
{
	unsigned int hash = hash_command(command);
	int i;

	for (i = 0; internal_commands[i].command_name != NULL; i++)
	{
		if (hash == hash_command(internal_commands[i].command_name))
		{
			if (_strcmp(command, internal_commands[i].command_name) == 0)
				return (internal_commands[i].func);
		}
	}

	return (NULL);
}

/**
 * _getenv - gets the value of an environment variable
 * @name: name of the environment variable
 *
 * Return: the value of the variable as a string
 */

char *_getenv(char *name)
{
	char **my_environ;
	char *pair_ptr;
	char *name_cpy;

	for (my_environ = environ; *my_environ != NULL; my_environ++)
	{
		for (pair_ptr = *my_environ, name_cpy = name;
				*pair_ptr == *name_cpy; pair_ptr++, name_cpy++)
		{
			if (*pair_ptr == '=')
				break;
		}
		if ((*pair_ptr == '=') && (*name_cpy == '\0'))
			return (pair_ptr + 1);
	}

	return (NULL);
}

