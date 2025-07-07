/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:50:48 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/07 13:55:44 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	mini_exec(t_cmd *cmd_node, t_env **env_list, char **env)
{
	if (cmd_node->cmd)
	{
		if (!is_builtin(cmd_node->cmd))
			help_exec_command(cmd_node->cmd, *env_list, env);
		else
			get_exit_status(handle_builtin(cmd_node->cmd, env_list), SET);
	}
	exit(get_exit_status(0, GET));
}

static int	handle_single_builtin(t_cmd *cmd, t_env **env_list)
{
	if (is_builtin(cmd->cmd) && !pipe_counter(cmd))
	{
		get_exit_status(handle_builtin(cmd->cmd, env_list), SET);
		return (1);
	}
	return (0);
}

void	exec_cmd(t_cmd *cmd_list, t_env *env_list, char **env, t_exec *exec)
{
	t_cmd	*tmp;
	int		i;
	t_hrdoc	**fds;

	i = -1;
	tmp = cmd_list;
	fds = set_get_hrd(GET, NULL);
	while (tmp)
	{
		if (!tmp->cmd)
		{
			tmp = tmp->next;
			continue ;
		}
		exec->children[++i] = fork();
		if (exec->children[i] == 0)
		{
			dup_fd(tmp, &i, exec, *fds);
			mini_exec(tmp, &env_list, env);
			exit(EXIT_FAILURE);
		}
		else if (exec->children[i] < 0)
			error_msg("fork");
		tmp = tmp->next;
	}
}

void	handle_cmd(t_cmd *cmd_list, t_env *env_list, char **env)
{
	t_exec	*exec_var;

	exec_var = NULL;
	if (g_sig == 1)
		return ;
	else if (handle_single_builtin(cmd_list, &env_list))
		return ;
	exec_var = malloc(sizeof(t_exec));
	if (!exec_var)
		error_msg("");
	exec_var->num_cmds = pipe_counter(cmd_list) + 1;
	init_pipe_ends(&exec_var);
	exec_cmd(cmd_list, env_list, env, exec_var);
	close_wait(exec_var->pipe_fds, 2 * (exec_var->num_cmds - 1),
		exec_var->children);
	free(exec_var);
}
