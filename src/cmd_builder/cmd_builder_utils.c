/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:45:09 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/12 06:11:19 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clear_directions(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp->file)
		{
			free(tmp->file);
			tmp->file = NULL;
		}
		free(tmp);
	}
}

void	clear_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->cmd)
		{
			tmp->cmd = NULL;
			free(tmp->cmd);
		}
		if (tmp->redir)
			clear_directions(tmp->redir);
		free(tmp);
		tmp = NULL;
	}
}

int	simple_cmd(int *f, t_tokens **token, t_cmd **cmd)
{
	t_cmd	*last;

	if (!is_redir(*token))
	{
		if (*f == 0)
		{
			add_cmd(cmd, new_cmd((*token)->content, NULL, CMD));
			*token = (*token)->next;
			*f = 1;
		}
		else
		{
			while (*token && !ispipe(*token) && !is_redir(*token))
			{
				last = last_cmd(cmd);
				if (last)
					last->cmd = join_it(last->cmd, (*token)->content);
				*token = (*token)->next;
			}
		}
		if (!*token)
			return (1);
	}
	return (0);
}

int	build_cmd_helper(t_tokens **token, t_cmd **cmd, int *f)
{
	if (!ispipe(*token))
	{
		if (simple_cmd(f, token, cmd))
			return (1);
		if (build_redir(f, token, cmd))
			return (1);
	}
	if (*token && ispipe(*token))
	{
		add_cmd(cmd, new_cmd(NULL, NULL, (*token)->type));
		*token = (*token)->next;
		*f = 0;
	}
	if (!(*token))
		return (1);
	return (0);
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
