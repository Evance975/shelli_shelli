#include "shell.h"

int check_file(char *full_path);

/**
 * find_program - function that finds a program in path.
 * @data: a variable rep pointer to the program data.
 * Return: (0)success, otherwise (errcode)
 */

int find_program(data_of_program *data)
{
	int q = 0, ret_code = 0;
	char **directories;

	if (!data->command_name)
		return (2);

	/*when full or executable in the same path; */
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	directories = tokenize_path(data);/* searching in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (q = 0; directories[q]; q++)
	{/* appending the function_name to PATH */
		directories[q] = str_concat(directories[q], data->tokens[0]);
		ret_code = check_file(directories[q]);
		if (ret_code == 0 || ret_code == 126)
		{/*file found, not a directory, has execute permisions*/
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(directories[q]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}

/**
 * tokenize_path - function that tokenizes the path in the directories.
 * @data: a variable rep a pointer to the program data.
 * Return: (array of path directories)When success
 */

char **tokenize_path(data_of_program *data)
{
	int q = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;

	/* geting the PATH in the value*/
	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{/*if PATH is not found*/
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	/* number of directories in the PATH found as below: */
	for (q = 0; PATH[q]; q++)
	{
		if (PATH[q] == ':')
			counter_directories++;
	}

	/* reserving the space for the array of pointer*/
	tokens = malloc(sizeof(char *) * counter_directories);

	/*tokenising and duplicating each token of path*/
	q = 0;
	tokens[q] = str_duplicate(_strtok(PATH, ":"));
	while (tokens[q++])
	{
		tokens[q] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * check_file - function that checks if a file exist, if not a dairectory and
 * if has excecution permisions for permisions to be granted..
 * @full_path: variable rep the pointer to the full file name.
 * Return: (0)success, or (error-code) if it present.
 */

int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/*if the file doesn;t exist*/
	errno = 127;
	return (127);
}
