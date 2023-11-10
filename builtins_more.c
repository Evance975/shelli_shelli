#include "shell.h"

/**
 * builtin_exit - function for exit of a program.
 * @data: variable rep the struct for the program data
 * Return: (0) if sucess, (non zero value) if failed
 */
int builtin_exit(data_of_program *data)
{
	int q;

	if (data->tokens[1] != NULL)
	{/*when argument for exit is found, check if it is a number*/
		for (q = 0; data->tokens[1][q]; q++)
			if ((data->tokens[1][q] < '0' || data->tokens[1][q] > '9')
				&& data->tokens[1][q] != '+')
			{/*When it is not a number:*/
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * builtin_cd - A function that changes the present working directory.
 * @data: var rep the struct for the program data.
 * Return: (0) if sucess, (non zero value) Fail.
 */
int builtin_cd(data_of_program *data)
{
	char *dir_home = env_get_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_old = env_get_key("OLDPWD", data);
			if (dir_old)
				error_code = set_work_directory(data, dir_old);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (error_code);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (set_work_directory(data, dir_home));
	}
	return (0);
}

/**
 * set_work_directory - function that set the working directory.
 * @data: variable rep the struct for the program data
 * @new_dir: variable rep the path to be set as a working directory
 * Return: (0)if sucess, or (non zero value provided in arguments)
 */
int set_work_directory(data_of_program *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * builtin_help - A function that shows the environment where our shell is run.
 * @data: variable rep the struct for the program data.
 * Return: (0)if sucess, or (non zero value passed in the argumeny)
 */
int builtin_help(data_of_program *data)
{
	int q, length = 0;
	char *mensajes[6] = {NULL};

	mensajes[0] = HELP_MSG;

	/* argument validation */
	if (data->tokens[1] == NULL)
	{
		_print(mensajes[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	mensajes[1] = HELP_EXIT_MSG;
	mensajes[2] = HELP_ENV_MSG;
	mensajes[3] = HELP_SETENV_MSG;
	mensajes[4] = HELP_UNSETENV_MSG;
	mensajes[5] = HELP_CD_MSG;

	for (q = 0; mensajes[q]; q++)
	{
		length = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], mensajes[q], length))
		{
			_print(mensajes[q] + length + 1);
			return (1);
		}
	}
	/*when no match present, print error and then return -1 */
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * builtin_alias - Function that manipulates aliases by (add, remove or show).
 * @data: variable rep the struct for the program data.
 * Return: (0)sucess, or (non zero value present as arguments).
 */
int builtin_alias(data_of_program *data)
{
	int q = 0;

	/* When no argument prent; print all env var */
	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++q])
	{/* When argument present; set or print env vars*/
		if (count_characters(data->tokens[q], "="))
			set_alias(data->tokens[q], data);
		else
			print_alias(data, data->tokens[q]);
	}

	return (0);
}
