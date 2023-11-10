#include "shell.h"

/**
 * builtin_env - functon that prints the environment where our shell is running.
 * @data: variable rep the struct for the program data.
 * Return: (zero) Sucess, or (non-zero value in the argument).
 */
/*DONE*/
int builtin_env(data_of_program *data)
{
	int q;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	/* if there's no argument: */
	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		for (q = 0; data->tokens[1][q]; q++)
		{/* checks for = char existance */
			if (data->tokens[1][q] == '=')
			{/* if variable with same name exist:*/
			/* temporarilly change it */
				var_copy = str_duplicate(env_get_key(cpname, data));
				if (var_copy != NULL)
					env_set_key(cpname, data->tokens[1] + q + 1, data);

				/* printing the environment */
				print_environ(data);
				if (env_get_key(cpname, data) == NULL)
				{/* if the variable does not exist in environ; print it */
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{/* old var value return*/
					env_set_key(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[q] = data->tokens[1][q];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - function for processing the environment.
 * @data: variable rep the struct for our program data.
 * Return: (zero) Sucess, or (non-zero value present in the arguments)
 */
int builtin_set_env(data_of_program *data)
{
	/* arguments validation */
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_unset_env - function for processing non-exixting environment.
 * @data: variable rep the struct for our program data.
 * Return: (0) Success.
 */
int builtin_unset_env(data_of_program *data)
{
	/* validate args */
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_remove_key(data->tokens[1], data);

	return (0);
}
