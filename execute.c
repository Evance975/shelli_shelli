#include "shell.h"
/**
 * execute - function that executes it's entire path variables.
 * @data: variable rep a pointer to the program data.
 * Return: (0) success,or (-1)Fail.
 */
int execute(data_of_program *data)
{
	int retval = 0, status;
	pid_t pidd;

	/*looking for programs builtins */
	retval = builtins_list(data);
	if (retval != -1)/*if builtins has the program; */
		return (retval);

	/*checking for the file system of the*/
	retval = find_program(data);
	if (retval)
	{/* when not found;*/
		return (retval);
	}
	else
	{/*When found;*/
		pidd = fork(); /* create aa new child process */
		if (pidd == -1)
		{ /*when fork fails;*/
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{/*the child process that execute the program*/
			retval = execve(data->tokens[0], data->tokens, data->env);
			if (retval == -1) /* if error when execve*/
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{/* parent process that wait and check the exit status of the child */
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
