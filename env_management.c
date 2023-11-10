#include "shell.h"

/**
 * env_get_key - function that gets the value of env vars.
 * @key: variable rep the environment variable of interest.
 * @data: variable rep the struct of the program data.
 * Return: (pointer to variable value) Success or(NULL) when not present.
 */
char *env_get_key(char *key, data_of_program *data)
{
	int q, key_length = 0;

	/*arguments validation */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* variable length requested */
	key_length = str_length(key);

	for (q = 0; data->env[q]; q++)
	{/* checking coincidence of variable name */
		if (str_compare(key, data->env[q], key_length) &&
		 data->env[q][key_length] == '=')
		{/* return key NAME=  when found*/
			return (data->env[q] + key_length + 1);
		}
	}
	/* return NULL when not found*/
	return (NULL);
}

/**
 * env_set_key - function that overwrite the value of the environment variable
 * or create it if does not exist.
 * @key: variable rep the name of the variable to set.
 * @value: variable rep the new value.
 * @data: variable rep the struct of the program data
 * Return: (1) if NULL, (2) if an error occured, (0) if sucess.
 */

int env_set_key(char *key, char *value, data_of_program *data)
{
	int q, key_length = 0, is_new_key = 1;

	/* argument validation */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* length of requested variable */
	key_length = str_length(key);

	for (q = 0; data->env[q]; q++)
	{/* checking coincidence of var name */
		if (str_compare(key, data->env[q], key_length) &&
		 data->env[q][key_length] == '=')
		{/* When coincidence found; */
			is_new_key = 0;
			/* free variable, create new one */
			free(data->env[q]);
			break;
		}
	}
	/* forming string in the form of key=value */
	data->env[q] = str_concat(str_duplicate(key), "=");
	data->env[q] = str_concat(data->env[q], value);

	if (is_new_key)
	{/* create a variable at the end of list if new*/
	/* put a NULL value in the nxt position*/
		data->env[q + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - function that removes a key from the environment.
 * @key: variable rep the key to be removed.
 * @data: variable rep the sructure of the program data.
 * Return: (1) key was removed, (0) key does not exist.
 */
int env_remove_key(char *key, data_of_program *data)
{
	int q, key_length = 0;

	/*argument validation*/
	if (key == NULL || data->env == NULL)
		return (0);

	/*length of requested variable*/
	key_length = str_length(key);

	for (q = 0; data->env[q]; q++)
	{/*checking for coincidence*/
		if (str_compare(key, data->env[q], key_length) &&
		 data->env[q][key_length] == '=')
		{/*remove key if found */
			free(data->env[q]);

			/*other keys moved one position down */
			q++;
			for (; data->env[q]; q++)
			{
				data->env[q - 1] = data->env[q];
			}
			/*adding NULL value at the end off the list */
			data->env[q - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - function that prints the current environ.
 * @data: variable rep the struct for the program data.
 * Return: void functiom. No return
 */
void print_environ(data_of_program *data)
{
	int r;

	for (r = 0; data->env[r]; r++)
	{
		_print(data->env[r]);
		_print("\n");
	}
}
