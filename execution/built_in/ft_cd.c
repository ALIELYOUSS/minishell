/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:01:59 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/05 21:53:39 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error_chdir(int chdir_return)
{
	if (chdir_return != 0)
		perror("");
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

static void	check_cd_args(char *path, t_env *env)
{
	char	*old_path;

	old_path = NULL;
	if (!ft_strcmp(path, "-"))
	{
		old_path = env_path(env, "OLDPWD");
		if (!old_path)
			return ;
		error_chdir(chdir(old_path));
	}
	else
		error_chdir(chdir(path));
}

int	ft_cd(char *prompt, t_env **env)
{
	char	*path;
	char	**paths;

	path = NULL;
	paths = ft_split(prompt, ' ');
	if (!paths)
		return (1);
	if (!paths[1])
	{
		path = env_path(*env, "HOME");
		if (!path)
			return (free_td(paths), ft_putstr_fd("HOME NOT SET", 2), 0);
		error_chdir(chdir(path));
		free(path);
		return (free_td(paths), 0);
	}
	if (paths[2] != NULL)
	{
		perror("cd: too many arguments");
		return (free_td(paths), 1);
	}
	check_cd_args(paths[1], *env);
	change_current_path(env);
	free_td(paths);
	return (0);
}
