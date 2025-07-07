/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 23:17:14 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/07 20:53:04 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	handle_redir(t_cmd *cmd_list, t_hrdoc *fds)
{
	t_redir	*tmp;
 
	tmp = cmd_list->redir;
	while (tmp)
	{
		if (tmp->type == OUT || tmp->type == APP)
		{
			dup2(cmd_list->out, 1);
			close(tmp->fd);
		}
		else if (tmp->type == IN)
		{
			dup2(cmd_list->in, 0);
			close(tmp->fd);
		}
		else if (tmp->type == HRDOC && fds && fds->fd)
			handle_heredoc_fd(fds);
		tmp = tmp->next;
	}
}
