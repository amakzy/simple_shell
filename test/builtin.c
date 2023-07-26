#include "shell.h"

/**
 * env - prints the current environment
 * @tokenized_command: command entered
 *
 * Return: void
 */
void env(char **tokenized_command __attribute__((unused)))
{
	int i = 0;

	while (environ[i] != NULL)
	{
		print(environ[i], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
		i++;
	}
}

/**
 * quit - exits the shell
 * @tokenized_command: command entered
 *
 * Return: void
 */
void quit(char **tokenized_command)
{
	int num_token = 0;
	int arg;

	while (tokenized_command[num_token] != NULL)
		num_token++;

	switch (num_token)
	{
		case 1:
			free(tokenized_command);
			free(line);
			free(commands);
			exit(status);
			break;

		case 2:
			arg = _atoi(tokenized_command[1]);

			if (arg == -1)
			{
				print(shell_name, STDERR_FILENO);
				print(": 1: exit: Illegal number: ", STDERR_FILENO);
				print(tokenized_command[1], STDERR_FILENO);
				print("\n", STDERR_FILENO);
				status = 2;
			}
			else
			{
				free(line);
				free(tokenized_command);
				free(commands);
				exit(arg);
			}
			break;
		default:
			print("$: exit doesn't take more than one argument\n", STDERR_FILENO);
			break;
	}
}
