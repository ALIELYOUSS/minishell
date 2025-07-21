/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:44:57 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/22 00:56:49 by alel-you         ###   ########.fr       */
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

int	error_handler(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i + 1] && str[i] == '"' && str[i + 1] == ' ')
			return (0);
		else if (str[i + 1] && str[i] == '\'' && str[i + 1] == ' ')
			return (0);
		i++;
	}
	return (1);
}

int	valid_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp && tmp->cmd != NULL)
		{
			if ((ft_strchr(tmp->cmd, '\'') || ft_strchr(tmp->cmd, '\"'))
				&& (!error_handler(tmp->cmd)) && !is_builtin(tmp->cmd))
			{
				get_exit_status(127, SET);
				return (printf("%s: command not found\n", tmp->cmd), 0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
