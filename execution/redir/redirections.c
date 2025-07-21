/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 23:17:14 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/22 00:04:48 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	herdoc_handler(char *delimiter, t_env *env_list)
{
	char	*input;
	char	*clean_delimiter;
	int		should_expand;
	int		fd[2];

	should_expand = has_quotes(delimiter);
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
			break ;
		input = process_heredoc_line(input, env_list, should_expand);
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
		free(input);
	}
	free(input);
	return (close(fd[1]), fd[0]);
}

void	help_dup_and_close(int fd, int flag)
{
	if ((flag == IN || flag == HRDOC) && (fd != -1))
	{
		if (dup2(fd, 0) == -1)
			error_msg("dup2: ");
	}
	else if ((flag == OUT || flag == APP) && (fd != -1))
	{
		if (dup2(fd, 1) == -1)
			error_msg("dup2: ");
	}
	else if (fd != -1)
		close(fd);
}

void	handle_redir(t_cmd **cmd_list)
{
	t_cmd	*tmp;
	t_redir	*tmp2;

	tmp = (*cmd_list);
	while (tmp)
	{
		tmp2 = (*cmd_list)->redir;
		while (tmp2)
		{
			if (tmp2->type == HRDOC)
				help_dup_and_close(tmp->hrd, HRDOC);
			else if (tmp2->type == IN)
				help_dup_and_close(tmp->in, IN);
			else if (tmp2->type == OUT)
				help_dup_and_close(tmp->out, OUT);
			else if (tmp2->type == APP)
				help_dup_and_close(tmp->out, APP);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}
