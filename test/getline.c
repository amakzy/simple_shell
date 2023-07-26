#include "shell.h"

/**
 * input_buffer - buffers chained commands
 * @inf: parameter struct
 * @buffer: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */

ssize_t input_buffer(dragon *inf, char *buffer, size_t *len)
{
	ssize_t z = 0;
	size_t len_p = 0;

	switch (*len)
	{
		case 0:
			free(buffer);
			buffer = NULL;
			signal(SIGINT, ccblocker);
#if USE_GETLINE
			z = getline(&buffer, &len_p, stdin);
#else
			z = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			len_p = (z > 0) ? (size_t)z : 0;
#endif
			if (z > 0)
			{
				if (buffer[z - 1] == '\n')
				{
					buffer[z - 1] = '\0';
					z--;
				}
				inf->linecount_flag = 1;
				remove_comment(buffer);
				make_history_list(inf, buffer, inf->histcount++);

				if (strchr(buffer, ';'))
				{
					*len = len_p;
					inf->cmd_buf = buffer;
				}
			}
			break;
		default:
			break;
	}
	return (z);
}

/**
 * line_input - gets a line minus the newline
 * @inf: parameter struct
 *
 * Return: bytes read
 */
ssize_t line_input(dragon *inf)
{
	static char buffer[BUFFER_SIZE];
	static size_t j, k, len;
	char **buf_p = &(inf->arg);
	ssize_t z = 0;
	char *p = NULL;

	putchar(BUFFER_FLUSH);
	z = input_buffer(inf, buffer, &len);

	if (z == -1)
		return (-1);

	if (len)
	{
		size_t k = j;

		check_name(inf, buffer, &k, j, len);
		while (k < len && !is_name(inf, buffer, &k))
			k++;
	}

	j = k + 1;
	if (j >= len)
	{
		j = len = 0;
		inf->cmd_buf_type = CMD_NORM;
	}

	*buf_p = p;
	return (k - j);

	*buf_p = buffer;
	return (z);
}

/**
 * ccblocker - blocks ctrl-C
 * @snom: the signal number
 *
 * Return: void
 */

void ccblocker(__attribute__((unused))int snom)
{
	switch (snom)
	{
		case SIGINT:
			puts("\n");
			puts("$ ");
			putchar(BUFFER_FLUSH);
			break;
		default:
			break;
	}
}
