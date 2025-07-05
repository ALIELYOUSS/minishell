/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:50:48 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/05 22:20:50 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int is_type(t_cmd *cmd_list, t_type to_find)
{
	t_cmd *tmp;

	tmp = cmd_list;
	while (tmp)
	{
		if (tmp->redir && tmp->redir->type == to_find)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void add_exit_status(t_env **env, int exit_status)
{
	t_env *tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->key)
		{
			if (!ft_strcmp(tmp->key, "?"))
			{
				tmp->value = ft_itoa(exit_status);
				break;
			}
		}
		tmp = tmp->next;
	}
}

void close_wait(int *pipe_fds, int len, int *children)
{
	int i;

	i = -1;
	while (++i < len)
		close(pipe_fds[i]);
	free(pipe_fds);
	if (children)
	{
		int status;

		status = 0;
		i = -1;
		while (++i < (len / 2) + 1)
		{
			waitpid(children[i], &status, 0);
			status = get_exit_status(status, SET);
		}
		if (WIFEXITED(status))
			get_exit_status(WEXITSTATUS(status), SET);
		if (WIFSIGNALED(status))
			get_exit_status(WEXITSTATUS(status) + 128, SET);
		free(children);
	}
}

void help_exec_command(char *cmd, t_env *env_list, char **env)
{
	char **command;
	char *cmd_path;

	if (!cmd || !cmd[0])
		return (ft_putstr_fd(" :command not found\n", 2));
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
		exit(get_exit_status(127, SET));
	}
	execve(cmd_path, command, env);
	ft_putstr_fd("exec failed\n", 2);
}

void mini_exec(t_cmd *cmd_node, t_env **env_list, char **env)
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

void handle_pipe(t_cmd *cmd_list, t_env *env_list, char **env, t_hrdoc *fds)
{
	int num_cmds;
	int i;
	int j;
	int *pipe_fds;
	t_cmd *tmp;
	pid_t *children;

	i = 0;
	j = -1;
	children = NULL;
	pipe_fds = NULL;
	num_cmds = pipe_counter(cmd_list) + 1;
	pipe_fds = init_pipe_ends(pipe_fds, num_cmds, &children);
	if (g_sig == 1)
		return ;
	tmp = cmd_list;
	if (is_builtin(tmp->cmd) && !pipe_counter(tmp))
		get_exit_status(handle_builtin(tmp->cmd, &env_list), SET);
	while (tmp)
	{
		if (!tmp->cmd && (tmp = tmp->next))
			continue ;
		children[i] = fork();
		if (children[i] == 0)
		{
			dup_fd(tmp, &i, num_cmds, pipe_fds, fds);
			mini_exec(tmp, &env_list, env);
			exit(EXIT_FAILURE);
		}
		else if (children[i] < 0)
			error_msg("fork");
		tmp = tmp->next;
		i++;
	}
	close_wait(pipe_fds, 2 * (num_cmds - 1), children);
}
