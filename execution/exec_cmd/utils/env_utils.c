/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:41:32 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/08 03:19:07 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	error_msg(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	td_len(char **str)
{
	int	i;

	i = 1;
	while (str[i])
		i++;
	return (i);
}

t_env	*create_env_node(char *var)
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

t_env	*fill_env_list(char **envp)
{
	int		i;
	t_env	*head;
	t_env	*tail;
	t_env	*node;

	head = NULL;
	tail = NULL;
	node = NULL;
	i = 0;
	while (envp[i])
	{
		node = create_env_node(envp[i]);
		if (!node)
			continue ;
		if (!head)
			head = node;
		else
			tail->next = node;
		tail = node;
		i++;
	}
	return (head);
}

char	*env_path(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
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
