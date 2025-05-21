/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali-elyouss <ali-elyouss@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:47:22 by alel-you          #+#    #+#             */
/*   Updated: 2024/11/17 03:19:32 by ali-elyouss      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*curr_node;

	if (!lst || !f)
		return ;
	curr_node = lst;
	while (curr_node)
	{
		f(curr_node->content);
		curr_node = curr_node->next;
	}
}
