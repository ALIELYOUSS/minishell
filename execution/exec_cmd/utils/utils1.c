/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:17:39 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/22 00:22:25 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	init_pipe_ends(t_exec **exec_var)
{
	int	i;

	i = -1;
	(*exec_var)->pipe_fds = ft_malloc(sizeof(int) * \
			(2 * (*exec_var)->num_cmds));
	(*exec_var)->children = ft_malloc(sizeof(pid_t) * (*exec_var)->num_cmds);
	if (!(*exec_var) || !(*exec_var)->pipe_fds)
		error_msg("malloc");
	while (++i < (*exec_var)->num_cmds - 1)
	{
		if (pipe((*exec_var)->pipe_fds + i * 2) == -1)
			error_msg("pipe");
	}
}

void	dup_fd(t_cmd *cmd_node, int *index, t_exec *exec_var)
{
	if (*index > 0)
		dup2(exec_var->pipe_fds[(*index - 1) * 2], 0);
	if ((*index < exec_var->num_cmds - 1 && cmd_node->next))
		dup2(exec_var->pipe_fds[*index * 2 + 1], 1);
	if (cmd_node->redir)
		handle_redir(&cmd_node);
	close_wait(exec_var->pipe_fds, 2 * (exec_var->num_cmds - 1), NULL);
}

static void	abs_path(char **command, char **env)
{
	if (!command || !*command)
		return ;
	if (command && ft_strchr(command[0], '/'))
		execve(command[0], command, env);
}

void	exec_error_case(char *cmd, int flag)
{
	if (cmd)
		ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	clear_all(flag);
}
