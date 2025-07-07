#include "../../inc/minishell.h"

void    error_msg(char *str)
{
	perror(str);
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

t_env *create_env_node(char *var)
{
	t_env	*node;
	size_t	eq_len;
	size_t	var_len;
	char	*eq;

	node = NULL;
	var_len = ft_strlen(var);
	eq = ft_strchr(var, '=');
	node = malloc(sizeof(t_env));
	if (!eq)
	{
		node->key = ft_strdup(var);
		if (!node->key)
			return (NULL);
		node->value = NULL;
	}
	else
	{
		eq_len = ft_strlen(eq);
		node->key = strndup(var, var_len - eq_len);
		node->value = ft_strdup(eq + 1);
		if (!node->key && node->value)
			return (NULL);
		else if (node->key && !node->value)
			return (NULL);
	}
	node->next = NULL;
	return (node);
}

char	**empty_env()
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * 5);
	if (!new_env)
		error_msg("");
	new_env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	new_env[1] = ft_strdup("SHLVL=1");
	new_env[2] = ft_strdup("PATH=/.local/bin:/.local/bin:/.local/bin:/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	new_env[3] = ft_strdup("_=/usr/bin/env");
	new_env[4] = NULL;
	return (new_env);
}

t_env *fill_env_list(char **envp)
{
	int    i;
	t_env   *head;
	t_env   *tail;
	t_env   *node;

	head = NULL;
	tail = NULL;
	node = NULL;
	i = 0;
	// if (!envp)
	// 	return(handle_empty_env());
	if (!envp)
		envp = empty_env();
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		node = create_env_node(envp[i]);
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

char *env_path(t_env *env, char *key)
{
	t_env	*tmp;
	char	*ret;

	tmp = env;
	ret = NULL;
	if (!tmp || !key)
	{
		perror("Error can not find path in env");
		return (NULL);
	}
	while (tmp)
	{
		if (tmp->key && ft_strcmp(tmp->key, key) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}
