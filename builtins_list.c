#include "shell.h"

/**
 * builtins_list - function that search matches then executes builtin.
 * @data: variable rep the struct for the program data.
 * Return: (function return type) Success, (-1) Fail
 **/
int builtins_list(data_of_program *data)
{
	int iterator;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

/*structure iteration*/
	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
/*code executed if match is present*/
		if (str_compare(options[iterator].builtin, data->command_name, 0))
		{
/*if success, return the value of the function*/
			return (options[iterator].function(data));
		}
/*else, return -1 */
	}
	return (-1);
}
