#include "shell.h"

#define BUFFER_SIZE 1024

static char buffer[BUFFER_SIZE];
static int buf_pos;
static int buf_size;
/**
 * my_getline - a simlpe getline function implementation
 * Return: a line
 */
char *my_getline(void)
{
	char *line = malloc(BUFFER_SIZE);
	int line_pos = 0;

	while (1)
	{
		/* Refill buffer if empty */
		if (buf_pos >= buf_size)
		{
			buf_pos = 0;
			buf_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		}

		/* Break on EOF or newline*/
		if (buf_pos >= buf_size)
		{
			break;
		}
		else if (buffer[buf_pos] == '\n')
		{
			buf_pos++;
			break;
		}

		/* Copy char from buffer to line*/
		line[line_pos++] = buffer[buf_pos++];

		/* Reallocate line buffer if full*/
		if (line_pos >= BUFFER_SIZE)
		{
			line = realloc(line, 2 * BUFFER_SIZE);
		}
	}

	line[line_pos] = '\0';

	return (line);
}
