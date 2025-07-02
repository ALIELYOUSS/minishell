/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:01:59 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/01 23:44:29 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	error_chdir(int chdir_return)
{
	if (chdir_return != 0)
		perror("cannot find path");
}

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

int	ft_cd(char *prompt, t_env **env)
{
	char	*path;
	char	**paths;

	path = NULL;
	paths = ft_split(prompt, ' ');
	if (!paths )
		return (1);
	if (!paths[1])
	{
		path = env_path(*env, "HOME");
		if (!path)
		{
			perror("HOME NOT SET");
			return (1);
		}
		error_chdir(chdir(path));
		free(path);
		return (free_td(paths), 0);
	}
	if (paths[2] != NULL)
	{
		perror("cd: too many arguments");
		return (1);
	}
	error_chdir(chdir(paths[1]));
	change_current_path(env);
	free_td(paths);
	return (0);
}
