/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:51:58 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/07 13:52:20 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	add_exit_status(t_env **env, int exit_status)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->key)
		{
			if (!ft_strcmp(tmp->key, "?"))
			{
				tmp->value = ft_itoa(exit_status);
				break ;
			}
		}
		tmp = tmp->next;
	}
}

int	is_type(t_cmd *cmd_list, t_type to_find)
{
	t_cmd	*tmp;

	tmp = cmd_list;
	while (tmp)
	{
		if (tmp->redir && tmp->redir->type == to_find)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	free_td(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
