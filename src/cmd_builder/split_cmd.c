/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:16:05 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/22 12:02:07 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	assign_node(t_cmd *node, t_redir *redir, t_type type)
{
	if (!node)
		return ;
	node->type = type;
	node->arg = NULL;
	node->redir = redir;
	node->in = -1;
	node->out = -1;
	node->hrd = -1;
	node->f = -1;
	node->next = NULL;
}

void	quote_case(char *arg, char *cmd, int *index, int *i)
{
	char	quote;

	quote = cmd[*index];
	arg[(*i)++] = cmd[(*index)++];
	while (cmd[*index] && cmd[*index] != quote)
		arg[(*i)++] = cmd[(*index)++];
	if (cmd[*index] == quote)
		arg[(*i)++] = cmd[(*index)++];
}

char	*expand_args_helper(char *cmd)
{
	int		index;
	int		i;

	i = 0;
	while (cmd[i] && cmd[i] != '$' )
		i++;
	if (!cmd[i])
		return (cmd);
	else if (cmd[i] == '$')
	{
		index = 0;
		cmd = simple_join(simple_join(bef_param(cmd, &i), ""), &cmd[index]);
	}
	return (cmd);
}

void	expand_args(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
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
			// non_expanded_change(tmp->arg);
		}
		tmp = tmp->next;
	}
}
