#include "shell.h"

/**
 * expand_variables - function that expand variables
 * @data: a variable rep a pointer to a struct of the program's data.
 * Return: none,sets errno.
 */
void expand_variables(data_of_program *data)
{
	int q, r;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (q = 0; line[q]; q++)
		if (line[q] == '#')
			line[q--] = '\0';
		else if (line[q] == '$' && line[q + 1] == '?')
		{
			line[q] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + q + 2);
		}
		else if (line[q] == '$' && line[q + 1] == '$')
		{
			line[q] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + q + 2);
		}
		else if (line[q] == '$' && (line[q + 1] == ' ' || line[q + 1] == '\0'))
			continue;
		else if (line[q] == '$')
		{
			for (r = 1; line[q + r] && line[q + r] != ' '; r++)
				expansion[r - 1] = line[q + r];
			temp = env_get_key(expansion, data);
			line[q] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + q + r);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expand_alias - function that expands alias+.
 * @data: a variable rep  pointer to a struct of the program's data.
 * Return: none, set errno.
 */
void expand_alias(data_of_program *data)
{
	int q, r, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (q = 0; line[q]; q++)
	{
		for (r = 0; line[q + r] && line[q + r] != ' '; r++)
			expansion[r] = line[q + r];
		expansion[r] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + q + r);
			line[q] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - function that append string at end of the buffer.
 * @buffer: variable rep the buffer to be filled.
 * @str_to_add: variable rep the string to be copied in the buffer
 * Return: none, set errno.
 */
int buffer_add(char *buffer, char *str_to_add)
{
	int length, q;

	length = str_length(buffer);
	for (q = 0; str_to_add[q]; q++)
	{
		buffer[length + q] = str_to_add[q];
	}
	buffer[length + q] = '\0';
	return (length + q);
}
