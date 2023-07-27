#include "shell.h"
#include <unistd.h>

/**
 * changeDirectory - change current directory cd.
 *
 * @args: number of arguments passed
 */
void changeDirectory(char **args)
{
	char cwd[1024];

	if (args[1] == NULL)
	{
		/* cd with no arguments - go home */
		char *home = getenv("HOME");

		if (home == NULL)
		{
			fprintf(stderr, "HOME not set\n");
		}
		else if (chdir(home) != 0)
		{
			perror("chdir failed");
		}
	} else if (strcmp(args[1], "-") == 0)
	{
		/* cd - */
		if (chdir(getenv("OLDPWD")) != 0)
		{
			perror("chdir failed");
		}
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("chdir failed");
		}
	}
	 /* Update PWD environment variable */

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		setenv("PWD", cwd, 1);
	}
	else
	{
		perror("getcwd failed");
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
