/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:03:07 by alel-you          #+#    #+#             */
/*   Updated: 2024/11/17 15:46:01 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*new_s1;
	unsigned char	*new_s2;

	i = 0;
	if (i == n)
		return (0);
	new_s1 = (unsigned char *)s1;
	new_s2 = (unsigned char *)s2;
	while (i < n - 1 && new_s1[i] == new_s2[i])
		i++;
	return (new_s1[i] - new_s2[i]);
}
