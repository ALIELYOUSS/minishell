/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 03:14:28 by yael-maa          #+#    #+#             */
/*   Updated: 2025/05/22 03:15:48 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_redir	*last_redir(t_redir **redir)
{
	t_redir	*tmp;

	if (!redir || !(*redir))
		return (NULL);
	tmp = *redir;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_redir	*new_redir(char *content, t_type type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = type;
	new->file = content;
	new->next = NULL;
}

void	add_redir(t_redir **redir, t_redir *new)
{
	t_redir	*tmp;

	if (!redir || !new)
		return (NULL);
	if (!(*redir))
		*redir = new;
	else
	{
		tmp = last_redir(redir);
		tmp->next = new;
	}
}
