/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:06:17 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/15 07:10:17 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_echo(char **args, int fd)
{
	if (!args || !args[0])
		return (1);
	
	if (fd < 0)
		fd = 1;
		
	return ft_echo(args, fd);
}

int	is_flag(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '-' && str[i] != 'n')
			return (0);
		else if (str[i + 1] && str[i] == 'n' && str[i + 1] == '-')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **str, int fd)
{
	int	i;
	int	flag;

	i = 1;
	if (!str || str[i] == NULL)
		return (ft_putchar_fd('\n', fd), 0);
	flag = is_flag(str[i]);
	if (flag == 1)
	{
		while (str[i] && is_flag(str[i]))
			i++;
	}
	while (str[i])
	{
		ft_putstr_fd(str[i], fd);
		if (str[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (!flag)
		ft_putchar_fd('\n', fd);
	return (0);
}
