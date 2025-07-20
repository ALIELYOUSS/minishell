/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 03:04:08 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/18 01:00:35 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static void	ft_free(t_env *node)
// {
// 	if (node->key)
// 		free(node->key);
// 	if (node->value)
// 		free(node->value);
// 	node->value = NULL;
// 	node->key = NULL;
// 	if (node)
// 		free(node);
// 	node = NULL;
// }

static int	check_node(t_env *node, char *unseted)
{
	if (node && node->next && node->next->key
		&& !ft_strcmp(node->next->key, unseted))
		return (1);
	return (0);
}

static int	unset_head(t_env **env, char *unseted)
{
	t_env	*tmp;

	tmp = *env;
	if (tmp && tmp->key && !ft_strcmp(tmp->key, unseted))
	{
		*env = tmp->next;
		// ft_free(tmp);
		tmp = NULL;
		return (1);
	}
	return (0);
}

int	ft_unset(t_env **env, char *unseted)
{
	t_env	*tmp;
	t_env	*tmp_1;

	if (!*env)
		return (1);
	if (unset_head(env, unseted))
		return (0);
	tmp = *env;
	while (tmp)
	{
		if (check_node(tmp, unseted))
		{
			tmp_1 = tmp->next;
			tmp->next = tmp_1->next;
			// ft_free(tmp_1); // Skip freeing - handled by garbage collector
			tmp_1 = NULL;
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	handle_unset(char **args, t_env **env)
{
	int	status;
	int	i;

	status = 0;
	i = 1;
	if (!args || !env || !*env)
		return (1);
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
			status = ft_unset(env, args[i]);
		i++;
	}
	return (status);
}
