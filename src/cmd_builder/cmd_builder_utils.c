/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:45:09 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/17 22:39:46 by alel-you         ###   ########.fr       */
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

void	close_node_fd(t_cmd *cmd)
{
	if (cmd->in != 0 && cmd->in != 1 && cmd->in != 2)
		close(cmd->in);
	if (cmd->out != 0 && cmd->out != 1 && cmd->out != 2)
		close(cmd->out);
	if (cmd->hrd != 0 && cmd->hrd != 1 && cmd->hrd != 2)
		close(cmd->hrd);
}

void	clear_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		close_node_fd(tmp);
		if (tmp->arg)
			ft_freearr(tmp->arg);
		if (tmp->cmd != NULL)
		{
			free(tmp->cmd);
			tmp->cmd = NULL;
		}
		if (tmp->redir != NULL)
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
			if (simple_helper(f, token, cmd))
				return (1);
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
