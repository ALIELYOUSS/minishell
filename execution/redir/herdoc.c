/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:59:50 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/04 18:27:51 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	herdoc_handler(char *delimiter, t_env *env_list)
{
	char	*input;
	int		line_len;
	int		fd[2];

	input = NULL;
	line_len = 0;
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
			input = here_doc_expansion(input, env_list);
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
		free(input);
	}
	close(fd[1]);
	return (fd[0]);
}

static void	open_hrdc_parsing(t_list *token, t_env *env_list)
{
	t_tokens	*tmp_t;
	int			fd;

	fd = 0;
	tmp_t = NULL;
	if (token && env_list == NULL)
	{
		tmp_t = token->head;
		fd = herdoc_handler(tmp_t->next->content, NULL);
		if (fd < 0)
			error_msg("open: ");
		close(fd);
	}
}

void	set_hrdoc_fd(t_cmd *cmd, t_env *env_list, t_list *token)
{
	t_cmd		*tmp;

	tmp = NULL;
	if (cmd)
	{
		tmp = cmd;
		while (tmp && env_list && g_sig != 1)
		{
			if (tmp->redir && tmp->redir->type == HRDOC)
			{
				tmp->redir->fd = herdoc_handler(tmp->redir->file, env_list);
				if (tmp->redir->fd < 0)
					error_msg("open: ");
			}	
			tmp = tmp->next;
		}
	}
	open_hrdc_parsing(token, env_list);
}
