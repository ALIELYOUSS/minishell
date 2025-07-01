/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:07:16 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/01 02:00:44 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);	
}

int	ft_exit(char *args)
{
	char	**splited;

	splited = ft_split(args, ' ');
	if (!splited)
		return (1);
	if (splited[1] && is_digit(splited[1]))
		g_exit_status = ft_atoi(splited[1]);
	else
		g_exit_status = 127;
	free_td(splited);
	ft_putstr_fd("exit\n", 1);
	exit(g_exit_status);
}
