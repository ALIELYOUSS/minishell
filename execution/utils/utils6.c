
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:12:55 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/07 01:51:51 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_node_to_garbage_list(t_garbage **gb_list, t_garbage *new_node)
{
	t_garbage	*tmp;

	tmp = NULL;
	if (!*gb_list)
	{
		*gb_list = new_node;
		return ;
	}
	else
	{
		tmp = *gb_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

t_garbage	*creat_garbage_node(void *content)
{
	t_garbage	*new_node;

	new_node = malloc(sizeof(t_garbage));
	if (!new_node)
		error_msg("");
	if (content)
	{
		new_node->address = content;
		new_node->next = NULL;
	}
	return (new_node);
}

t_garbage	**get_garbage_list(int flag)
{
	static t_garbage *gb_list;
	
	if (flag == GET)
		return (&gb_list);
	return (&gb_list);
}

void	* ft_malloc(void *ptr_to_free, size_t size)
{
	t_garbage	**garbage_list;
	t_garbage			*new;
	
	garbage_list = get_garbage_list(GET);
	ptr_to_free = malloc(size);
	new = NULL;
	if (!ptr_to_free)
		error_msg("");
	new = creat_garbage_node(ptr_to_free);
	add_node_to_garbage_list(garbage_list, new);
	return (ptr_to_free);
}

void	free_garbage_coll(void)
{
	t_garbage	**gb_list;
	t_garbage	*tmp;
	t_garbage	*current;

	tmp = NULL;
	gb_list = get_garbage_list(GET);
	current = *gb_list;
	while (current->next)
	{
		tmp = current->next;
		if (current && current->address)
			free(current->address);
		free(current);
		current = tmp;
	}
	*gb_list = NULL;
}