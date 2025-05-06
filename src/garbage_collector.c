/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:40:01 by yael-maa          #+#    #+#             */
/*   Updated: 2025/05/06 21:16:45 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_tokens	*ft_lstlast(t_tokens *lst)
{
	int	last;
	int	i;

	if (!lst)
		return (NULL);
	last = ft_lstsize(lst) - 1;
	i = 0;
	while (i < last)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}

t_garbage	*add_garbage(void *ptr, t_tokens *tokens)
{
	t_garbage	*garbage;

	garbage = malloc(sizeof(t_garbage));
	if (!garbage)
		return (NULL);
	garbage->ptr = ptr;
	garbage->tokens = tokens;
	garbage->next = NULL;
	return (garbage);
}

void	garbage_collector(t_garbage **garbage, t_garbage *new)
{
	t_tokens	*tmp;

	if (!garbage || !new)
		return ;
	if (!*garbage)
		*garbage = new;
	else
	{
		tmp = ft_lstlast(*garbage);
		tmp->next = new;
	}
}

void	free_node_garbage(t_garbage *garbage)
{
	if (!garbage)
		return ;
	if (garbage->ptr)
		free(garbage->ptr);
	if (garbage->tokens)
		clear_list(garbage->tokens);
}

void	free_garbage(t_garbage *garbage)
{
	t_garbage	*tmp;

	while (garbage)
	{
		tmp = garbage;
		garbage = garbage->next;
		free_node_garbage(tmp);
		free(tmp);
	}
}
