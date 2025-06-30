/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:50:48 by alel-you          #+#    #+#             */
/*   Updated: 2025/06/30 17:22:08 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_type(t_cmd *cmd_list, t_type to_find)
{
	t_cmd	*tmp;

	tmp = cmd_list;
	while (tmp)
	{
		if (tmp->redir && tmp->redir->type == to_find)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*find_delimiter(t_cmd *cmd_list, t_type to_find)
{
	t_cmd	*tmp;

	tmp = cmd_list;
	while (tmp)
	{
		if (tmp->redir && tmp->redir->type == to_find)
			return (ft_strdup(tmp->redir->file));
		tmp = tmp->next;
	}
	return (NULL);
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->cmd)
			printf("%s\n", tmp->cmd);
		else
			printf("%d\n", tmp->type);
		tmp = tmp->next;
	}
}

void	close_wait(int *p, int p_size, int *children)
{
	int	i;

	i = -1;
	while (++i < p_size)
		close(p[i]);
	if (children)
	{
		int status;
		
		status = 0;
		i = -1;
		while (++i < (p_size / 2) + 1)
			waitpid(children[i], &status, 0);
		// g_exit_status = WIFEXITED(status);
		// if (WIFEXITED(status) && WEXITSTATUS(status))
			// printf("%d\n", status);
		free(children);
	}
}

void	handle_pipe(t_cmd *cmd_list, t_env *env_list, char **env)
{
	int		num_cmds;
	int		i;
	int		j;
	int		*pipe_fds;
	t_cmd	*tmp;
	pid_t	*children;

	i = 0;
	j = -1;
	children = NULL;
	pipe_fds = NULL;
	num_cmds = pipe_counter(cmd_list) + 1;
	pipe_fds = init_pipe_ends(pipe_fds, num_cmds, &children);
	set_hrdoc_fd(cmd_list, env);
	tmp = cmd_list;
	while (tmp)
	{
		if (!tmp->cmd)
		{
			tmp = tmp->next;
			continue ;
		}
		children[i] = fork();
		if (children[i] < 0)
			error_msg("fork");
		if (children[i] == 0)
		{
			dup_fd(tmp, &i, num_cmds, pipe_fds);
			if (!is_builtin(tmp->cmd))
				exec(tmp->cmd, env_list, env);
			else
			{
				handle_builtin(tmp->cmd, env_list);
				exit(EXIT_SUCCESS);
			}
			exit(EXIT_FAILURE);
		}
		tmp = tmp->next;
		i++;
	}
	close_wait(pipe_fds, 2 * (num_cmds - 1), children);
}

int	is_redirection(t_cmd *cmd, t_type to_find)
{
	t_cmd *tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->redir && tmp->redir->type == to_find)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	execution(t_cmd *cmd_list, char **env, t_env *env_list)
{
	t_cmd	*tmp;
	int		hrdoc_fd;

	hrdoc_fd = 0;
	tmp = cmd_list;
	if (tmp && tmp->cmd && is_builtin(tmp->cmd) && !pipe_counter(cmd_list))
		handle_builtin(tmp->cmd, env_list);
	else
		handle_pipe(cmd_list, env_list, env);
	return (0);
}
