/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:26:31 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/17 07:11:53 by alel-you         ###   ########.fr       */
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
	char	*cwd_temp;
	char	*new_pwd;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
		{
			change_old_path(env, tmp->value);
			cwd_temp = getcwd(NULL, 0);
			if (cwd_temp)
			{
				new_pwd = ft_strdup(cwd_temp);
				free(cwd_temp);
				tmp->value = new_pwd;
			}
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

int	exit_status(int exit_status)
{
	if (exit_status < 0 && val_abs(exit_status) > 256)
		return ((exit_status - 256) - 256);
	else if (exit_status > 0 && exit_status > 256)
		return (exit_status - 256);
	return (exit_status);
}

int	is_valid_identifier(char *str)
{
	int	i;

	i = 1;
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
