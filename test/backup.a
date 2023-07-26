#include "shell.h"

#include "shell.h"

/**
 * myexit - exits the shell
 * @inf: Structure containing potential arguments.
 *  Return: exits with a given exit status
 *         (0) if inf.argv[0] != "exit"
 */
int myexit(info_t *inf)
{
	int exitchk;

	switch (inf->argc)
	{
	case 1:
		inf->err_num = -1;
		return (-2);
	case 2:
		exitchk = _erratoi(inf->argv[1]);

		if (exitchk == -1)
			int myexit(info_t *inf);

		{
			inf->status = 2;
			print_error(inf, "Illegal number: ");
			_eputs(inf->argv[1]);
			_eputchar('\n');

			return (1);
		}
		inf->err_num = _erratoi(inf->argv[1]);

		return (-2);
	default:
		inf->status = 2;
		print_error(inf, "exit: too many arguments\n");
		return (1);
	}
}

/**
 * mycd - changes the current directory of the process
 * @inf: Structure containing potential arguments.
 *  Return: Always 0
 */
int mycd(info_t *inf)
{
	char *str, *directory, buffer[1024];
	int chdir_r;

	switch (inf->argc)
	{
	case 1:
		directory = _getenv(inf, "HOME=");
		if (!directory)
			chdir_r = chdir((directory = _getenv(inf, "PWD=")) ? directory : "/");
		else
			chdir_r = chdir(directory);
		break;
	case 2:

	if (_strcmp(inf->argv[1], "-") == 0)
	{
		directory = _getenv(inf, "OLDPWD=");
		if (!directory)
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(directory);
		_putchar('\n');
		chdir_r = chdir(directory);
		else
		chdir_r = chdir(inf->argv[1]);
		break;
	default:
		inf->status = 2;
		print_error(inf, "cd: too many arguments\n");
		return (1);
	}

	if (chdir_r == -1)
	{
		print_error(inf, "can't cd to ");
		_eputs(inf->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

