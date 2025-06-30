/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:04:42 by alel-you          #+#    #+#             */
/*   Updated: 2025/06/30 17:17:23 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int    herdoc_handler(char *delimiter, char **env)
{
	char    *input;
	int     line_len;
	int     fd[2];
	
	input = NULL;
	line_len = 0;
	if (pipe(fd) == -1)
		error_msg("pipe");
	setup_herdoc_signals(1);
	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		line_len = ft_strlen(input);
		if (!ft_strcmp(input, delimiter))
		{
			free(input);
			break ;
		}
		if (ft_strchr(input, '$'))
			input = here_doc_expansion(input, env);
		write(fd[1], input, line_len);
		write(fd[1], "\n", 1);
		free(input);
	}
	close(fd[1]);
	return (fd[0]);
}

void    exec_heredoc_cmd(t_cmd *cmd_list, char **env, t_env *env_list)
{
	int     child;
	int     wait_child;
	t_cmd   *tmp;
	char    *delimiter;

	delimiter = find_delimiter(cmd_list, HRDOC);
	if (!delimiter)
		error_msg("error");
	set_hrdoc_fd(cmd_list, env);
	tmp = cmd_list;
	child = fork();
	if (tmp->redir && tmp->redir->type == HRDOC)
	{
		if (!child)
		{
			if (dup2(tmp->redir->fd, 0) == -1)
				error_msg("dup2");
			if (tmp->cmd && !is_builtin(tmp->cmd))
				exec(tmp->cmd, env_list, env);
			else if (tmp->cmd)
				handle_builtin(tmp->cmd, env_list);
			exit(EXIT_FAILURE);
		}
		close(tmp->redir->fd);
	}
	else if (child == -1)
		error_msg("fork");
	waitpid(child, &wait_child, 0);
}

void    set_hrdoc_fd(t_cmd *cmd, char **env)
{
	t_cmd		*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->redir && tmp->redir->type == HRDOC)
			tmp->redir->fd = herdoc_handler(tmp->redir->file, env);
		tmp = tmp->next;
	}
}
