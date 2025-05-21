/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:03:06 by alel-you          #+#    #+#             */
/*   Updated: 2024/11/20 00:52:25 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_absolut(int a)
{
	long	tmp;

	tmp = a;
	if (tmp < 0)
	{
		tmp = -tmp;
		return (tmp);
	}
	return (tmp);
}

static int	ft_a_len(int a)
{
	long	tmp;
	int		len;

	tmp = 0;
	len = 0;
	if (a < 0)
	{
		len++;
		tmp = ft_absolut(a);
	}
	else
		tmp = a;
	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int a)
{
	int		len;
	char	*str;
	long	tmp;

	if (a == -0)
		return (ft_strdup("0"));
	len = ft_a_len(a);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	if (a < 0)
		tmp = ft_absolut(a);
	else
		tmp = a;
	while (len >= 0)
	{
		str[len] = (tmp % 10) + '0';
		tmp /= 10;
		len--;
	}
	if (a < 0)
		str[0] = '-';
	return (str);
}
