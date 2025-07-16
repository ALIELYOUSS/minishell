/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:50:48 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/16 06:45:37 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	mini_exec(t_cmd *cmd_node, t_env **env_list, char **env)
{
	if (cmd_node->cmd)
	{
		if (cmd_node && cmd_node->cmd && !is_builtin(cmd_node->cmd))
			help_exec_command(cmd_node->cmd, *env_list, env);
		else if (cmd_node)
			get_exit_status(handle_builtin(cmd_node, env_list), SET);
	}
	exit(EXIT_FAILURE);
}

static int	handle_single_builtin(t_cmd *cmd, t_env **env_list)
{
	if (cmd && cmd->cmd
		&& is_builtin(cmd->cmd) && !pipe_counter(cmd))
	{
		get_exit_status(handle_builtin(cmd, env_list), SET);
		return (1);
	}
	return (0);
}

void	exec_cmd(t_cmd *cmd_list, t_env *env_list, char **env, t_exec *exec)
{
	t_cmd	*tmp;
	int		i;

	i = -1;
	tmp = cmd_list;
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
			dup_fd(tmp, &i, exec);
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
