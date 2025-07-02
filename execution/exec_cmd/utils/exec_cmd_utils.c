/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:42:00 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/02 18:35:23 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	handle_redir(t_redir *redir)
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
        else if (tmp->type == IN || tmp->type == HRDOC)
        {
            dup2(tmp->fd, 0);
            close(tmp->fd);
        }
        tmp = tmp->next;
    }
}

int	*init_pipe_ends(int *pipe_ends, int num_cmds, int **children)
{
	int	i;

	i = -1;
	pipe_ends = malloc(sizeof(int) * (2 * (num_cmds)));
	(*children)= malloc(sizeof(pid_t) * num_cmds);
	if (!(*children) || !pipe_ends)
		error_msg("malloc");
	while (++i< num_cmds - 1)
	{
		if (pipe(pipe_ends + i * 2) == -1)
			error_msg("pipe");
	}
	return (pipe_ends);		
}


void	dup_fd(t_cmd *cmd_node, int *index, int num_cmds, int *pipe_fds)
{
	if (*index > 0)
		dup2(pipe_fds[(*index - 1) * 2], 0);
	if ((*index < num_cmds - 1 && cmd_node->next))
		dup2(pipe_fds[*index * 2 + 1], 1);
	if (cmd_node->redir)
		handle_redir(cmd_node->redir);
	close_wait(pipe_fds, 2 * (num_cmds - 1), NULL);
}

int	get_exit_status(int exit_st, int flg)
{
	static int value;

	if (flg == SET)
		value = exit_st;
	return (value);
}
