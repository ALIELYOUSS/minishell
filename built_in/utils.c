#include "../minishell.h"

void    error_msg(char *str)
{
    printf("%s\n", str);
    exit(EXIT_FAILURE);
}

int td_len(char **str)
{
    int i;

    i = 1;
    while (str[i])
        i++;
    return (i);
}

t_env *create_env_node(const char *var)
{
    t_env *node;
    size_t  eq_len;
    size_t  var_len;
    
    node = malloc(sizeof(t_env));
    if (!node)
        return NULL;
    char *eq = ft_strchr(var, '=');
    puts(eq);
    var_len = ft_strlen(var);
    eq_len = ft_strlen(eq);
    if (!eq)
    {
        node->key = strdup(var);
        node->value = NULL;
    }
    else
    {
        node->key = strndup(var, var_len - eq_len);
        node->value = ft_strdup(eq + 1);
    }
    node->next = NULL;
    return (node);
}

t_env *fill_env_list(char **envp)
{
    int    i;
    t_env   *head;
    t_env   *tail;
    
    head = NULL;
    tail = NULL;
    i = 0;
    while (envp[i])
    {
        t_env *node = create_env_node(envp[i]);
        if (!node)
            continue;
        if (!head)
            head = node;
        else
            tail->next = node;
        tail = node;
        i++;
    }
    return (head);
}
