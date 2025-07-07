/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:50:48 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/07 01:32:17 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static int	process_child_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

void	close_wait(int *pipe_fds, int len, int *children)
{
	int	i;
	int	status;
	int	last_exit_status;

	i = 0;
	last_exit_status = 0;
	while (i < len)
	{
		close(pipe_fds[i]);
		i++;
	}
	free(pipe_fds);
	if (children)
	{
		i = 0;
		while (i < (len / 2) + 1)
		{
			waitpid(children[i], &status, 0);
			last_exit_status = process_child_status(status);
			i++;
		}
		get_exit_status(last_exit_status, SET);
		free(children);
	}
}

void	help_exec_command(char *cmd, t_env *env_list, char **env)
{
	char	**command;
	char	*cmd_path;

	if (!cmd || !cmd[0])
	{
		ft_putstr_fd(" :command not found\n", 2);
		exit(127);
	}
	cmd_path = NULL;
	command = ft_split(cmd, ' ');
	if (ft_strchr(command[0], '/'))
	{
		free(cmd_path);
		execve(command[0], command, env);
	}
	cmd_path = return_path(command[0], env_list);
	if (!cmd_path)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(" :command not found\n", 2);
		exit(127);
	}
	execve(cmd_path, command, env);
	ft_putstr_fd("exec failed\n", 2);
	exit(126);
}

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

	i = 0;
	tmp = cmd_list;
	fds = set_get_hrd(GET, NULL);
	while (tmp)
	{
		if (!tmp->cmd)
		{
			tmp = tmp->next;
			continue ;
		}
		exec->children[i] = fork();
		if (exec->children[i] == 0)
		{
			dup_fd(tmp, &i, exec, *fds);
			mini_exec(tmp, &env_list, env);
			exit(EXIT_FAILURE);
		}
		else if (exec->children[i] < 0)
			error_msg("fork");
		tmp = tmp->next;
		i++;
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
	close_wait(exec_var->pipe_fds, 2 * (exec_var->num_cmds - 1), exec_var->children);
	free(exec_var);
}
