/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 23:17:14 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/05 21:25:34 by alel-you         ###   ########.fr       */
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
		if (tmp->next && tmp->type == HRDOC && tmp->next->type == WORD && i < (*hrd_fd)->size)
		{
			(*hrd_fd)->fd[i++] = herdoc_handler(tmp->next->content, env_list);		
			continue ;
		}
		tmp = tmp->next;
	}
}