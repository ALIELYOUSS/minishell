/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:06:17 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/16 04:17:02 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] != '-')
		return (0);
	while (str[++i] && !ft_isspace(str[i]))
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

int	ft_echo(char **str, int fd)
{
	int	i;
	int	flag;
	int	j;
	int	x;

	i = 1;
	j = 0;
	if (!str)
		return (1);
	if (!str[i])
		return (free_td(str), ft_putchar_fd('\n', fd), 0);
	flag = is_flag(str[i]);
	if (flag == 1)
		i++;
	while (str[i])
	{
		x = 0;
		while (str[i][x])			
		{
			if (str[i][x] == '$')
			{
				while (str[i][x] && !ft_isspace(str[i][x]))
					x++;
				j = x;
				while (str[i][j] && ft_isspace(str[i][j]))
					j++;
				if (!str[i])
					write(1, "\n", 1);
			}
			if (str[i][x])
			{
				ft_putchar_fd(str[i][x], fd);
				x++;
			}
		}
		if (str[i + 1])
			ft_putchar_fd(' ', fd);
		if (str[i])
			i++;
	}
	if (!flag)
		ft_putchar_fd('\n', fd);
	return (free_td(str), 0);
}
