#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>
#include <stddef.h>
#include <fcntl.h>


/*constants*/
#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define PATH_COMMAND 3
#define INVALID_COMMAND -1

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define BUFFER_SIZE 1024

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* for read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define HIST_FILE ".shell_history"
#define HIST_MAX 1000

/**
 *struct map - a struct that maps a command name to a function 
 *
 *@command_name: name of the command
 *@func: the function that executes the command
 */

typedef struct map
{
	char *command_name;
	void (*func)(char **command);
} function_map;

typedef struct list_s
{
	int num;
	char *str;
	struct list_s *next;
} list_t;

typedef struct info
{
	int linecount_flag;
	int histcount;
	list_t *history;
	char *arg;
	char* cmd_buf;
	int cmd_buf_type; /* CMD_type ||, &&, ; */
} dragon;

extern char **environ;
extern char *line;
extern char **commands;
extern char *shell_name;
extern int status;

/*helpers*/
void print(char *, int);
char **tokenizer(char *, char *);
void remove_newline(char *);
int _strlen(char *);
void _strcpy(char *, char *);

/*helpers2*/
int _strcmp(char *, char *);
char *_strcat(char *, char *);
size_t _strspn(char *str1, char *str2);
size_t _strcspn(char *str1, char *str2);
char *_strchr(char *s, int c);

/*helpers3*/
char *_strtok_r(char *, char *, char **);
int _atoi(char *);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void ctrl_c_handler(int);
void remove_comment(char *);

/*utils*/
int parse_command(char *);
void execute_command(char **, int);
char *check_path(char *);
void (*get_func(char *))(char **);
char *_getenv(char *);

/*built_in*/
void env(char **);
void quit(char **);

/*getline.c*/
ssize_t input_buffer(dragon *inf, char *buffer, size_t *len);
ssize_t line_input(dragon *inf);
void ccblocker(int snom);
int check_name(dragon *inf, char *buffer, size_t *k, size_t j, size_t len);
int is_name(dragon *inf, char *buffer, size_t *k);

/*history*/
int make_history_list(dragon *inf, char *buffer, int linecount);
int write_history(dragon *inf);
int read_history(dragon *inf);
int renumber_history(dragon *inf);
void add_node_end(list_t **head, char *str, int num);
void delete_node_at_index(list_t **head, int index);
char *get_history_file(dragon *inf);

/*main*/
extern void non_interactive(void);
extern void initializer(char **current_command, int type_command);

#endif /*SHELL_H*/
