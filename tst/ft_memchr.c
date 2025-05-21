/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:09:16 by alel-you          #+#    #+#             */
/*   Updated: 2024/11/20 03:59:12 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char			*new_s;
	size_t			i;
	unsigned char	chr;

	if (n == 0)
		return (NULL);
	new_s = (char *)s;
	i = 0;
	chr = c;
	while (i < n)
	{
		if ((unsigned char)new_s[i] == chr)
			return (&new_s[i]);
		i++;
	}
	return (NULL);
}
