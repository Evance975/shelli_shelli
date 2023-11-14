#include "my_shell.h"

/**
 * my_builtins_list - function that searches matches then executes a builtin.
 * @data: variable representing the struct for the program data.
 * Return: (function return type) Success, (-1) Fail
 **/
int my_builtins_list(data_of_program *data)
{
    int iterator;
    my_builtins options[] = {
        {"exit", my_builtin_exit},
        {"help", my_builtin_help},
        {"cd", my_builtin_cd},
        {"alias", my_builtin_alias},
        {"env", my_builtin_env},
        {"setenv", my_builtin_set_env},
        {"unsetenv", my_builtin_unset_env},
        {NULL, NULL}
    };

    /* structure iteration */
    for (iterator = 0; options[iterator].builtin != NULL; iterator++)
    {
        /* code executed if match is present */
        if (my_str_compare(options[iterator].builtin, data->command_name, 0))
        {
            /* if success, return the value of the function */
            return (options[iterator].function(data));
        }
    }
    /* if no match is found, return -1 */
    return (-1);
}
