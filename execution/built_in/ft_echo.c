/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:06:17 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/17 03:39:00 by alel-you         ###   ########.fr       */
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

	i = 1;
	if (!str)
		return (1);
	if (!str[i])
		return (ft_putchar_fd('\n', fd), 0);
	flag = is_flag(str[i]);
	if (flag == 1)
		i++;
	while (str[i])
	{
		process_echo_line(str[i], fd);
		if (str[i + 1])
			ft_putchar_fd(' ', fd);
		if (str[i])
			i++;
	}
	if (!flag)
		ft_putchar_fd('\n', fd);
	return (0);
}
