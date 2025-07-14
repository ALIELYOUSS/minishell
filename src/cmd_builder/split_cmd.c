/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:16:05 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/14 19:28:14 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_args_helper(char *cmd)
{
	int		index;
	char	*leak_tracker;
	int		i;

	i = 0;
	leak_tracker = NULL;
	while (cmd[i] && cmd[i] != '$' )
		i++;
	if (!cmd[i])
		return (cmd);
	else if (cmd[i] == '$')
	{
		index = 0;
		free(var_name(cmd, &i, &index));
		leak_tracker = simple_join(bef_param(cmd, &i), "");
		cmd = simple_join(leak_tracker, &cmd[index]);
	}
	return (cmd);
}

void	expand_args(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		arr[i] = expand_args_helper(arr[i]);
		i++;
	}
}

void	split_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = (*cmd);
	while (tmp)
	{
		tmp->arg = NULL;
		if (tmp->cmd)
		{
			tmp->arg = args(tmp->cmd);
			expand_args(tmp->arg);
		}
		tmp = tmp->next;
	}
}
