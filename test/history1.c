#include "shell.h"

/**
 * make_history_list - adds entry to a history linked list
 * @inf: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int make_history_list(dragon *inf, char *buffer, int linecount)
{
	list_t *node = NULL;

	if (inf->history)
		node = inf->history;

	add_node_end(&node, buffer, linecount);

	if (!inf->history)
		inf->history = node;

	return (0);
}

