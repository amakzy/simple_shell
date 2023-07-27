#include "shell.h"
#include <unistd.h>

/**
 * getEnvVar - get environment variable
 *
 * @name: name of assigned variable
 * Return: null
 */
char *getEnvVar(const char *name)
{
	int i;
	int len = strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
		{
			return (&environ[i][len + 1]);
		}
	}
	return (NULL);
}
/**
 * asprintf - Calling vsnprintf and allocate mem
 * @strp: calling library
 * @fmt: assign memory
 * Return: idontknow
 */
int asprintf(char **strp, const char *fmt, ...)
{
	va_list ap;
	int size;

	va_start(ap, fmt);
	size = vsnprintf(NULL, 0, fmt, ap);
	va_end(ap);

	*strp = malloc(size + 1);
	if (*strp == NULL)
	{
		return (-1);
	}

	va_start(ap, fmt);
	size = vsnprintf(*strp, size + 1, fmt, ap);
	va_end(ap);

	return (size);
}
/**
 * setEnvVar - set/update environment variable
 *
 * @name : name of assigned variable
 * @value: value of assigned variable
 */
void setEnvVar(const char *name, const char *value)
{
	char *envString;

	asprintf(&envString, "%s=%s", name, value);
	putenv(envString);
}

/**
 * unsetEnvVar - unset environment variable
 *
 * @name: name of unassigned variable
 * Return: nothing
 */
void unsetEnvVar(const char *name)
{
	int i;
	int len = strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
		{
			free(environ[i]);
			while (environ[i] != NULL)
			{
				environ[i] = environ[i + 1];
				i++;
			}
			return;
		}
	}
}
