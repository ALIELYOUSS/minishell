/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 23:17:14 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/07 01:28:11 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	herdoc_handler(char *delimiter, t_env *env_list)
{
	char	*input;
	char	*expanded;
	int		fd[2];

	input = NULL;
	if (pipe(fd) == -1)
		error_msg("pipe");
	while (1)
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
		{
			expanded = here_doc_expansion(input, env_list);
			free(input);
			input = expanded;
		}
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
		free(input);
	}
	close(fd[1]);
	return (fd[0]);
}

void	here_doc(t_tokens *token, t_env *env_list, t_hrdoc **hrd_fd)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = token;
	if (!tmp)
		return ;
	(*hrd_fd)->fd = malloc(sizeof(int) * (*hrd_fd)->size);
	while (tmp)
	{
		if (tmp->next && tmp->type == HRDOC
			&& tmp->next->type == WORD && i < (*hrd_fd)->size)
		{
			(*hrd_fd)->fd[i] = herdoc_handler(tmp->next->content, env_list);
			i++;
			continue ;
		}
		tmp = tmp->next;
	}
}

void	handle_heredoc_fd(t_hrdoc *fds)
{
	int	i;

	i = 0;
	while (i < fds->size)
	{
		if (dup2(fds->fd[i], 0) == -1)
			error_msg("");
		close(fds->fd[i]);
		i++;
	}
	free(fds);
}

void	handle_redir(t_redir *redir, t_hrdoc *fds)
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
		else if (tmp->type == IN)
		{
			dup2(tmp->fd, 0);
			close(tmp->fd);
		}
		else if (tmp->type == HRDOC && fds->fd)
			handle_heredoc_fd(fds);
		tmp = tmp->next;
	}
}
