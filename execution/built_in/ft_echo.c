/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:06:17 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/07 21:06:07 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_echo(t_cmd *cmd_list)
{
	char	**splited;
	int		status;

	splited = NULL;
	status = 1;
	if (ft_strncmp(cmd_list->cmd, "echo", ft_strlen(cmd_list->cmd)) == 0)
		return (printf("\n"), 1);
	splited = ft_split(cmd_list->cmd, ' ');
	if (!splited)
		return (1);
	if (!cmd_list->redir)
		cmd_list->out = 1;
	status = ft_echo(splited, cmd_list->out);
	free_td(splited);
	return (status);
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
	if (str[i] == NULL)
		return (0);
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
