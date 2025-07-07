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

static int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

static char	*remove_quotes_from_delimiter(char *delimiter)
{
	char	*clean_delimiter;
	int		i;
	int		j;

	clean_delimiter = malloc(ft_strlen(delimiter) + 1);
	if (!clean_delimiter)
		return (NULL);
	i = 0;
	j = 0;
	while (delimiter[i])
	{
		if (delimiter[i] != '"' && delimiter[i] != '\'')
			clean_delimiter[j++] = delimiter[i];
		i++;
	}
	clean_delimiter[j] = '\0';
	return (clean_delimiter);
}

static char	*process_heredoc_line(char *input, t_env *env_list, int should_expand)
{
	char	*expanded;

	if (ft_strchr(input, '$') && env_list && should_expand)
	{
		expanded = here_doc_expansion(input, env_list);
		free(input);
		return (expanded);
	}
	return (input);
}

int	herdoc_handler(char *delimiter, t_env *env_list)
{
	char	*input;
	char	*clean_delimiter;
	int		should_expand;
	int		fd[2];

	should_expand = !has_quotes(delimiter);
	clean_delimiter = remove_quotes_from_delimiter(delimiter);
	if (pipe(fd) == -1)
		error_msg("pipe");
	while (1)
	{
		g_sig = 2;
		input = readline("> ");
		if (!input)
			break ;
		if (!ft_strcmp(input, clean_delimiter) || g_sig == 1)
		{
			free(input);
			break ;
		}
		input = process_heredoc_line(input, env_list, should_expand);
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
		free(input);
	}
	free(clean_delimiter);
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
		else if (tmp->type == HRDOC && fds && fds->fd)
			handle_heredoc_fd(fds);
		tmp = tmp->next;
	}
}
