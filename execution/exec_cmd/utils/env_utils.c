/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:41:32 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/08 03:34:37 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	set_env_key_value(t_env *node, char *var, char *eq)
{
	int	eq_pos;

	if (!eq)
	{
		node->key = ft_strdup(var);
		node->value = NULL;
	}
	else
	{
		eq_pos = eq - var;
		node->key = ft_substr(var, 0, eq_pos);
		node->value = ft_strdup(eq + 1);
	}
}

void	add_env_node(t_env **head, t_env **tail, t_env *node)
{
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
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
	char	*eq;

	if (!var)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	eq = ft_strchr(var, '=');
	set_env_key_value(node, var, eq);
	if (!node->key)
		return (free(node), NULL);
	node->f = 0;
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
	i = 0;
	while (envp[i])
	{
		node = create_env_node(envp[i]);
		if (!node)
		{
			i++;
			continue ;
		}
		add_env_node(&head, &tail, node);
		i++;
	}
	return (head);
}
