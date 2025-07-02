/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:04:42 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/02 18:48:27 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int    herdoc_handler(char *delimiter, t_env *env_list)
{
	char    *input;
	int     line_len;
	int     fd[2];
	
	input = NULL;
	line_len = 0;
	if (pipe(fd) == -1)
		error_msg("pipe");
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1 )
	{
		g_sig = 2;
		input = readline("> ");
		if (!input)
			break ;
		if (!ft_strcmp(input, delimiter) || g_sig == 1)
		{
			free(input);
			break ;
		}
		if (ft_strchr(input, '$') && env_list)
			input = here_doc_expansion(input, env_list);
		write(fd[1], input, ft_strlen(input));
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
	set_hrdoc_fd(cmd_list, env_list, NULL);
	tmp = cmd_list;
	child = fork();
	if (tmp->redir && tmp->redir->type == HRDOC)
	{
		if (!child)
		{
			printf("%d\n", tmp->redir->fd);
			if (dup2(tmp->redir->fd, 0) == -1)
				error_msg("dup2");
			if (tmp->cmd && !is_builtin(tmp->cmd))
				exec(tmp->cmd, env_list, env);
			else if (tmp->cmd)
				handle_builtin(tmp->cmd, &env_list);
			exit(get_exit_status(0, GET));
		}
		close(tmp->redir->fd);
	}
	else if (child == -1)
		error_msg("fork");
	waitpid(child, &wait_child, 0);
}

void    set_hrdoc_fd(t_cmd *cmd, t_env *env_list, t_list *token)
{
	t_cmd		*tmp;
	t_tokens		*tmp_t;

	tmp = NULL;
	tmp_t = NULL;
	if (cmd)
	{
		tmp = cmd;
		while (tmp && env_list && g_sig != 1)
		{
			if (tmp->redir && tmp->redir->type == HRDOC)
			{
				tmp->redir->fd = herdoc_handler(tmp->redir->file, env_list);
			}
			tmp = tmp->next;
		}
	}
	if (token && env_list == NULL)
    {
		int	fd;
        tmp_t = token->head;
        fd = herdoc_handler(tmp_t->next->content, NULL);
		close(fd);
	}
}
