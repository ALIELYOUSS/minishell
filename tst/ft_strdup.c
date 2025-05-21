/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali-elyouss <ali-elyouss@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:01:52 by alel-you          #+#    #+#             */
/*   Updated: 2024/11/17 02:29:58 by ali-elyouss      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char const *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char const *str)
{
	char	*dup;
	int		len;

	len = ft_strlen(str);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_strcpy(dup, str);
	return (dup);
}
