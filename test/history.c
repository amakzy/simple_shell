#include "shell.h"


/**
 * get_history_file - gets the history file
 * @inf: parameter struct
 *
 * Return: allocated string containing history file
 */
char *get_history_file(dragon *inf)
{
	char *buffer;
	char *home = getenv("HOME");
	size_t dir_len;

    
	if (!home)
		return NULL;

	dir_len = strlen(home);
	size_t READ_BUFFER_SIZE = dir_len + strlen(HIST_FILE) + 2;

	buffer = malloc(sizeof(char) * READ_BUFFER_SIZE);
	if (!buffer)
		return NULL;

	strcpy(buffer, home);
	strcat(buffer, "/");
	strcat(buffer, HIST_FILE);

	return (buffer);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @inf: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(dragon *inf)
{
    char *filename = get_history_file(inf);
    if (!filename)
        return -1;

     list_t *node;

    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    free(filename);
    if (fd == -1)
        return -1;

        for (node = inf->history; node; node = node->next)
    {
        write(fd, node->str, strlen(node->str));
        write(fd, "\n", 1);
    }

    close(fd);
    return 1;
}

/**
 * read_history - reads history from file
 * @inf: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(dragon *inf)
{
    char *filename = get_history_file(inf);
    int fd;
    struct stat st;

    if (!filename)
        return 0;
    
    fd = open(filename, O_RDONLY);
    free(filename);
    if (fd == -1)
        return 0;

    if (fstat(fd, &st) == -1)
    {
        close(fd);
        return 0;
    }

    off_t fsize = st.st_size;
    if (fsize < 2)
    {
        close(fd);
        return 0;
    }

    char *buffer = malloc(sizeof(char) * (fsize + 1));
    if (!buffer)
    {
        close(fd);
        return 0;
    }

    ssize_t rdlen = read(fd, buffer, fsize);
    close(fd);
    if (rdlen <= 0)
    {
        free(buffer);
        return 0;
    }

    buffer[fsize] = '\0';
    int linecount = 0;
    int last = 0;
    int i;

    for (i = 0; i < fsize; i++)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            make_history_list(inf, buffer + last, linecount++);
            last = i + 1;
        }
    }

    if (last != fsize)
        make_history_list(inf, buffer + last, linecount);

    free(buffer);
    inf->histcount = linecount;

    while (inf->histcount >= HIST_MAX)
        delete_node_at_index(&(inf->history), 0);

    read_history(inf);
    return inf->histcount;
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @inf: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(dragon *inf)
{
	list_t *node = inf->history;

	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	inf->histcount = i;

	return (i);
}

