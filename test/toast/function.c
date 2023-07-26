#include "shell.h"

/**
 * initializer - starts executing everything
 * @current_command: try to check current token
 * @type_command: parse token
 *
 * Return: void
 */
void initializer(char **current_command, int type_command)
{
	pid_t PID;

	switch (type_command)
	{
		case EXTERNAL_COMMAND:
		case PATH_COMMAND:
			PID = fork();

			if (PID == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (PID == 0)
			{
				execute_command(current_command, type_command);
				exit(EXIT_SUCCESS);
			}
			else
			{
				int child_status;

				if (waitpid(PID, &child_status, 0) == -1)
				{
					perror("waitpid");
					exit(EXIT_FAILURE);
				}

				status = WEXITSTATUS(child_status);
			}
			break;

		default:
			execute_command(current_command, type_command);
			break;
	}
}
