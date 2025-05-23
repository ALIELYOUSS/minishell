#include "../minishell.h"

static t_env *help_export(t_env *env)
{
    t_env   *tmp;
    char    *var;

    tmp = env;
    while (tmp)
    {
        tmp->key = ft_strjoin("declare -x ", tmp->key);
        tmp = tmp->next;
    }
    return (tmp);
}

void    ft_export(char *prompt, t_env *env)
{
    char    **splited;
    int     i;
    t_env   *export;
    export = help_export(env);
}

