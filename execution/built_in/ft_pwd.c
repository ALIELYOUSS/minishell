/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:08:12 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/17 05:06:29 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**set_pwd_get(int flag, char *pwd)
{
	static char	*stt_pwd;

	if (flag == SET && pwd != NULL)
	{
		free(stt_pwd);
		stt_pwd = pwd;
	}
	else if (flag == FREE)
		free(stt_pwd);
	return (&stt_pwd);
}

int	ft_pwd(char **args, int fd)
{
	char	*pwd;

	if (!args)
		return (1);
	pwd = getcwd(NULL, 0);
	if (pwd)
		set_pwd_get(SET, pwd);
	else if (!pwd)
		pwd = *set_pwd_get(GET, pwd);
	if (args[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (free_td(args), free(pwd), 1);
	}
	ft_putstr_fd(pwd, fd);
	ft_putchar_fd('\n', fd);
	return (free_td(args), 0);
}
