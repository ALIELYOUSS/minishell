/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:43:02 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/16 22:57:22 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*last_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!cmd || !*cmd)
		return (NULL);
	tmp = *cmd;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_cmd	*new_cmd(char *content, t_redir *redir, t_type type)
{
	t_cmd	*new;

	new = ft_malloc(sizeof(t_cmd), sizeof(t_cmd));
	if (!new)
		return (write(2, "Memory Error\n", 13), NULL);
	if (content)
	{
		new->cmd = content;
		if (!new->cmd)
			return (write(2, "Memory Error\n", 13), NULL);
	}
	else
		new->cmd = NULL;
	assign_node(new, redir, type);
	return (new);
}

char	*join_it(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	if (!s1 && !s2)
		return (NULL);
	s3 = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 2, ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!s3)
		return (write(2, "Memory Error\n", 13), NULL);
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	s3[i++] = ' ';
	j = -1;
	while (s2[++j])
		s3[i + j] = s2[j];
	s3[i + j] = '\0';
	return (s3);
}

void	add_cmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tmp;

	if (!cmd || !new)
		return ;
	if (!(*cmd))
		*cmd = new;
	else
	{
		tmp = last_cmd(cmd);
		tmp->next = new;
	}
}

t_cmd	*build_cmd(t_list *tokens)
{
	t_tokens	*token;
	t_cmd		*cmd;
	int			f;

	cmd = NULL;
	if (!tokens || !tokens->head)
		return (NULL);
	f = 0;
	token = tokens->head;
	while (token)
	{
		if (build_cmd_helper(&token, &cmd, &f))
			break ;
	}
	return (cmd);
}
