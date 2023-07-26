#include "shell.h"

/**
 * non_interactive - handles non_interactive mode
 *
 * Return: void
 */

void non_interactive(void)
{
	char **current_command = NULL;
	int i, type_command = 0;
	size_t n = 0;

	if (!isatty(STDIN_FILENO))
	{
		while (getline(&line, &n, stdin) != -1)
		{
			remove_newline(line);
			remove_comment(line);
			commands = tokenizer(line, ";");

			for (i = 0; commands[i] != NULL; i++)
			{
				current_command = tokenizer(commands[i], " ");

				if (current_command[0] == NULL)
				{
					free(current_command);
					break;
				}

				type_command = parse_command(current_command[0]);

				switch (type_command)
				{
					case INTERNAL_COMMAND:
					case EXTERNAL_COMMAND:
					case PATH_COMMAND:
						initializer(current_command, type_command);
						break;
					default:
						fprintf(stderr, "Unsupported command: %s\n", current_command[0]);
						break;
				}
				free(current_command);
			}

			free(commands);
		}

		free(line);
		exit(status);
	}
}
