/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 03:04:08 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/04 18:25:48 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_free(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

static int	check_node(t_env *node, char *unseted)
{
	if ((node->next && node->next->key && !ft_strncmp(node->next->key, \
		unseted, ft_strlen(node->next->key))))
	{
		return (1);
	}
	return (0);
}

int	ft_unset(t_env **env, char *unseted)
{
	t_env	*tmp;
	t_env	*tmp_1;

	tmp = *env;
	tmp_1 = *env;
	if (!*env)
		return (1);
	if (tmp && tmp->key && !ft_strcmp(tmp->key, unseted))
	{
		*env = tmp->next;
		ft_free(tmp);
		return (0);
	}
	while (tmp)
	{
		if (check_node(tmp, unseted))
		{
			tmp_1 = tmp->next;
			tmp->next = tmp_1->next;
			ft_free(tmp);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	handle_unset(char *prompt, t_env **env)
{
	char	**splited;

	splited = ft_split(prompt, ' ');
	if (!splited)
		return (1);
	else if (td_len(splited) > 2)
		return (0);
	if (splited[1])
		return (ft_unset(env, splited[1]));
	return (0);
}
