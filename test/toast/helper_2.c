#include "shell.h"

char *_strtok_r(char *string, char *delim, char **save_ptr)
{
	char *finish;

	switch (string == NULL)
	{
		case 1:
			string = *save_ptr;
			break;
	}

	switch (*string == '\0')
	{
		case 1:
			*save_ptr = string;
			return (NULL);
	}

	string += _strspn(string, delim);

	switch (*string == '\0')
	{
		case 1:
			*save_ptr = string;
			return (NULL);
	}

	finish = string + _strcspn(string, delim);

	switch (*finish == '\0')
	{
		case 1:
			*save_ptr = finish;
			return (string);
	}
	*finish = '\0';
	*save_ptr = finish + 1;
	return (string);
}

int _atoi(char *s)
{
	unsigned int n = 0;
	int result = 0;

	do {
		switch (*s)
		{
			case '-':
				result = -1;
				break;
			case '\0':
				if (n > 0)
				{
					result = (int)n;
					break;
				}
				result = -1;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				n = (n * 10) + (*s - '0');
				break;
			default:
				result = (-1);
				break;
		}
		s++;
	} while (*s);

	return (result);
}

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *temp_block;
	unsigned int i;

	if (ptr == NULL)
	{
		temp_block = malloc(new_size);
			return (temp_block);
	}
	if (new_size == old_size)
	{
		return (ptr);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	temp_block = malloc(new_size);

	if (temp_block != NULL)
	{
		for (i = 0; i < (old_size < new_size ? old_size : new_size); i++)
		{
			*((char *)temp_block + i) = *((char *)ptr + i);
		}

		free(ptr);
		return (temp_block);
	}
	else
	{
		return (NULL);
	}
}

void ctrl_c_handler(int signum)
{
	switch (signum)
	{
		case SIGINT:
			print("\n($) ", STDIN_FILENO);
			break;
	}
}

void remove_comment(char *input)
{
	int i = 0;

	switch (input[i] == '#')
	{
		case 1:
			input[i] = '\0';
			break;
	}

	while (input[i] != '\0')
	{
		switch (input[i] == '#' && input[i - 1] == ' ')
		{
			case 1:
				break;
		}

		i++;
	}

	input[i] = '\0';
}

