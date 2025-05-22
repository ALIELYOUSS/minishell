/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:04:21 by alel-you          #+#    #+#             */
/*   Updated: 2024/11/20 03:43:24 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*rest;
	size_t	len;

	rest = NULL;
	if (size != 0 && count > MAX_SIZE / size)
		return (rest);
	len = count * size;
	rest = malloc(len);
	if (!rest)
		return (NULL);
	ft_memset(rest, 0, len);
	return (rest);
}
