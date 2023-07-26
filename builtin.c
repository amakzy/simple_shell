#include "shell.h"
#include <unistd.h>

/**
 * changeDirectory - change current directory cd.
 *
 * @args: number of arguments passed
 */
void changeDirectory(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Expected argument to cd\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("chdir failed");
		}
	}
}

/**
 * printEnvVariables - print environment variables for the shell.
 */
void printEnvVariables(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}

/**
 * exitShell - exit the shell.
 *
 * @args: number of arguments passed
*/
void exitShell(char **args)
{
	if (args[1] != NULL)
	{
		exit(atoi(args[1]));
	}
	exit(0);
}
