/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:00:47 by alel-you          #+#    #+#             */
/*   Updated: 2024/11/20 03:56:28 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*current_lst;

	if (!lst)
		return (0);
	i = 0;
	current_lst = lst;
	while (current_lst)
	{
		i++;
		current_lst = current_lst->next;
	}
	return (i);
}
