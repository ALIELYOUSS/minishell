#include "minishell.h"

t_env *create_env_node(const char *var)
{
    t_env *node;
    size_t  eq_len;
    size_t  var_len;
    
    node = malloc(sizeof(t_env));
    if (!node)
        return NULL;
    char *eq = ft_strchr(var, '=');
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


void ft_env(char **env)
{
    t_env *env_list;
    t_env *current;
    
    
    env_list = fill_env_list(env);
    current = env_list;
    while (current)
    {
        if (current->value)
            printf("%s=%s\n", current->key, current->value);
        else
            printf("%s\n", current->key);
        current = current->next;
    }
}