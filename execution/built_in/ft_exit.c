/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:07:16 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/06 20:10:07 by alel-you         ###   ########.fr       */
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

int	val_abs(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

void	_exit_(int exit_status)
{
	if (exit_status < 0 && val_abs(exit_status) > 256)
		exit((val_abs(exit_status) - 256) - 256);
	else if (exit_status > 0 && exit_status > 256)
		exit(exit_status - 256);
	else
	{
		printf("exit\n");
		exit(exit_status);
	}
}

static void	free_env_list(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

int	ft_exit(char *args, t_env *env_list)
{
	char	**splited;
	int		exit_status;

	splited = ft_split(args, ' ');
	if (!splited)
		return (1);
	if (splited[2])
	{
		ft_putstr_fd(": too many argumment\n", 1);
		return (1);
	}
	if (splited[1] && is_digit(splited[1]))
	{
		exit_status = ft_atoi(splited[1]);
		free_td(splited);
		free_env_list(env_list);
		_exit_(exit_status);
	}
	return (0);
}
