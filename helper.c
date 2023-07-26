#include "shell.h"

/**
 *  * tokenizer - tokenizes input and stores it into an array
 *   * @input_string: input to be parsed
 *    * @delim: delimiter to be used, needs to be one character string
 *     *
 *      * Return: array of tokens
 */
char **tokenizer(char *input_string, char *delim)
{
	int num_delim = 0;
	char **av = NULL;
	char **val = NULL;
	char *token = _strtok_r(input_string, delim, &input_string);

	while ((token = _strtok_r(NULL, delim, &input_string)) != NULL)
	{
		av = _realloc(av, sizeof(*av) * num_delim, sizeof(*av) * (num_delim + 1));
		av[num_delim++] = token;
	}
	val = _realloc(av, sizeof(*av) * num_delim, sizeof(*av) * (num_delim + 1));
	av = val;
	av[num_delim] = NULL;

	return (av);
}

/**
 *  * print - Output Strings on console
 *   * @string: Array of characters
 *    * @stream: Output streams to console
 *     * Return: Always 0
 */

void print(char *string, int stream)
{
	while (*string)
		write(stream, string++, 1);
}

/**
 *  * remove_newline - removes new line from a string
 *   * @str: string to be used
 *    *
 *     * Return: void
 */
void remove_newline(char *str)
{
	while (*str)
	{
		if (*str == '\n')
		{
			*str = '\0';
			break;
		}
		str++;
	}
}

/**
 *  * _strcpy - copies a string to another buffer
 *   * @source: source to copy from
 *    * @dest: destination to copy to
 *     *
 *      * Return: void
 */
void _strcpy(char *source, char *dest)
{
	while ((*dest++ = *source++))
		;
}

/**
 *  * _strlen - counts string length
 *   * @string: string to be counted
 *    *
 *     * Return: length of the string
 */
int _strlen(char *string)
{
	int len = 0;

	if (string != NULL)
		while (*string++)
			len++;

	return (len);
}

