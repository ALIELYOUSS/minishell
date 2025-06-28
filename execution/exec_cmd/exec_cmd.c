/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:50:48 by alel-you          #+#    #+#             */
/*   Updated: 2025/06/28 02:09:57 by alel-you         ###   ########.fr       */
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

void	dial_alah_tsalawsmiatazbi(t_redir *redir)
{
	if (redir->type == OUT || redir->type == APP)
		dup2(redir->fd, 1);
	else if (redir->type == IN || redir->type == HRDOC)
		dup2(redir->fd, 0);
}

void	close_pipe_ends(int *p, int p_size)
{
	int	i;

	i = -1;
	while (++i < p_size)
		close(p[i]);
}

void	handle_pipe(t_cmd *cmd_list, t_env *env_list, char **env)
{
	int		num_cmds;
	int		i;
	int		j;
	int		flag;
	int		*pipe_fds;
	t_cmd	*tmp;
	pid_t	*children;

	i = 0;
	j = -1;
	flag = -1;
	num_cmds = pipe_counter(cmd_list) + 1;
	children = malloc(sizeof(pid_t) * num_cmds);
	pipe_fds = malloc(sizeof(int) * (2 * (num_cmds)));
	if (!children || !pipe_fds)
		error_msg("malloc");
	while (++j < num_cmds - 1)
	{
		if (pipe(pipe_fds + j * 2) == -1)
			error_msg("pipe");
	}
	set_hrdoc_fd(cmd_list, NULL);
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
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (children[i] == 0)
		{
			if (i > 0)
				dup2(pipe_fds[(i - 1) * 2], 0);
			else if (i < num_cmds - 1 && tmp->next)
				dup2(pipe_fds[i * 2 + 1], 1);
			if (tmp->redir)
				dial_alah_tsalawsmiatazbi(tmp->redir);
			close_pipe_ends(pipe_fds, 2 * (num_cmds - 1));
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
	j = -1;
	while (++j < 2 * (num_cmds - 1))
		close(pipe_fds[j]);
	j = -1;
	while (++j < num_cmds)
		waitpid(children[j], NULL, 0);
	free(children);
	free(pipe_fds);
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
