/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hrd_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:04:46 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/13 06:31:39 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void	here_doc(t_list *tokens, t_env *env_list)
// {
// 	t_tokens	*tmp;
// 	int			i;

// 	tmp = tokens->head;
// 	i = 0;
// 	// (*hrd_fd)->fd = malloc((sizeof(int) * (*hrd_fd)->size));
// 	// if (!tmp || !((*hrd_fd)->fd))
// 		// return ;
// 	while (tmp)
// 	{
// 		if (tmp->type == HRDOC && tmp->next && tmp->next->content
// 			&& tmp->next->type == WORD && i < (*hrd_fd)->size)
// 		{
// 			(*hrd_fd)->fd[i++] = herdoc_handler(tmp->next->content, env_list);
// 			tmp = tmp->next;
// 			continue ;
// 		}
// 		tmp = tmp->next;
// 	}
// }

char	*remove_quotes_from_delimiter(char *delimiter)
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

int	has_quotes(char *str)
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

char	*process_heredoc_line(char *input, t_env *env_list, int should_expand)
{
	char	*expanded;

	expanded = NULL;
	if (ft_strchr(input, '$') && env_list && should_expand)
	{
		expanded = here_doc_expansion(input, env_list);
		free(input);
		return (expanded);
	}
	return (input);
}
