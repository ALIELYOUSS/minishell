/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:43:02 by yael-maa          #+#    #+#             */
/*   Updated: 2025/05/23 01:23:06 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*join_it(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	return (s3);
}

void    build_cmd(t_list *tokens, t_cmd **cmd, t_redir **redir)
{
	t_tokens    *tmp;
	char		*cmd_l;

	tmp = tokens->head;
	while (tmp)
	{
		if (tmp && !operator(tmp))
		{		
			if (tmp->type == WORD || parenthese(tmp))
			{
				add_cmd(cmd, new_cmd(tmp->content, NULL, CMD));
				while (tmp && !operator(tmp) && !is_redir(tmp))
				{
					last_cmd(cmd)->cmd = join_it(last_cmd(cmd)->cmd, tmp->content);
					tmp = tmp->next;
				}
			}
			if (is_redir(tmp))
			{
				if (!(*cmd))
					add_cmd(cmd, new_cmd(NULL, new_redir(tmp->next->content, tmp->type), tmp->type));
				else
					last_cmd(cmd)->redir = new_redir(tmp->next->content, tmp->type);
				tmp = tmp->next;
				while (tmp && tmp->type == WORD)
				{
					tmp = tmp->next;
					if (is_redir(tmp))
					{
						add_redir(&last_cmd(cmd)->redir, new_redir(tmp->next->content, tmp->type));
						tmp = tmp->next;
					}
				}
			}
		}
		else
			add_cmd(cmd, new_cmd(NULL, NULL, tmp->type));
		tmp = tmp->next;
	}
}
