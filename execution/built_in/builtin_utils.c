/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:26:31 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/07 13:38:51 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	change_old_path(t_env **env_list, char *old_path)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			tmp->value = old_path;
			break ;
		}
		tmp = tmp->next;
	}
}

void	change_current_path(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
		{
			change_old_path(env, tmp->value);
			tmp->value = getcwd(NULL, 0);
			break ;
		}
		tmp = tmp->next;
	}
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
