/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:17:39 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/06 18:55:02 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	handle_heredoc_fd(t_hrdoc *fds)
{
	int	i;

	i = -1;
	while (++i < fds->size)
	{
		if (dup2(fds->fd[i], 0) == -1)
			error_msg("");
		close(fds->fd[i]);
	}
	free(fds);
}

void	handle_redir(t_redir *redir, t_hrdoc *fds)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->type == OUT || tmp->type == APP)
		{
			dup2(tmp->fd, 1);
			close(tmp->fd);
		}
		else if (tmp->type == IN)
		{
			dup2(tmp->fd, 0);
			close(tmp->fd);
		}
		else if (tmp->type == HRDOC && fds->fd)
			handle_heredoc_fd(fds);
		tmp = tmp->next;
	}
}

int	*init_pipe_ends(int *pipe_ends, int num_cmds, int **children)
{
	int	i;

	i = -1;
	pipe_ends = malloc(sizeof(int) * (2 * (num_cmds)));
	(*children) = malloc(sizeof(pid_t) * num_cmds);
	if (!(*children) || !pipe_ends)
		error_msg("malloc");
	while (++i < num_cmds - 1)
	{
		if (pipe(pipe_ends + i * 2) == -1)
			error_msg("pipe");
	}
	return (pipe_ends);
}

void	dup_fd(t_cmd *cmd_node, int *index, int num_cmds, int *pipe_fds, t_hrdoc *fds)
{
	if (*index > 0)
		dup2(pipe_fds[(*index - 1) * 2], 0);
	if ((*index < num_cmds - 1 && cmd_node->next))
		dup2(pipe_fds[*index * 2 + 1], 1);
	if (cmd_node->redir)
		handle_redir(cmd_node->redir, fds);
	close_wait(pipe_fds, 2 * (num_cmds - 1), NULL);
}
