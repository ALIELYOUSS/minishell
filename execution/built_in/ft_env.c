#include "../../inc/minishell.h"

int is_printable(char *cmd)
{
    int i;

    i = -1;
    while (cmd[++i])
    {
        if (cmd[i] == '=')
            return (1);
    }
    return (-1);
}

void ft_env(t_env *env)
{
    t_env *current;

    current = env;
    while (current)
    {
        if (current->value)
            printf("%s=%s\n", current->key, current->value);
        // else
        //     printf("%s\n", current->key);
        current = current->next;
    }
}