/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:12:55 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/07 01:52:43 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	tmp;

	i = 0;
	sign = 1;
	tmp = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = (tmp * 10) + (str[i] - '0');
		i++;
	}
	tmp *= sign;
	return (tmp);
}
