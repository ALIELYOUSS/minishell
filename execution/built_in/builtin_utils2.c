/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:44:57 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/17 05:06:14 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	process_echo_line(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			while (str[i] && !ft_isspace(str[i]))
				i++;
		}
		if (str[i])
		{
			ft_putchar_fd(str[i], fd);
			i++;
		}
	}
}

char	**leak_killer(char *str, int flag)
{
	static char	*to_free;

	if (flag == SET && str != NULL)
	{
		if (to_free != NULL)
			free(to_free);
		to_free = str;
	}
	else if (flag == FREE)
		free(to_free);
	return (&to_free);
}
