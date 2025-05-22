/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:22:19 by alel-you          #+#    #+#             */
/*   Updated: 2024/11/17 17:57:57 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_node;
	void	*f_f;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		f_f = f(lst->content);
		new_node = ft_lstnew(f_f);
		if (!new_node)
		{
			del(f_f);
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, new_node);
		lst = lst->next;
	}
	return (new);
}
