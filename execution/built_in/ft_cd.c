/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:01:59 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/15 06:11:17 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error_chdir(int chdir_return)
{
	if (chdir_return != 0)
		perror("");
}

static void	check_cd_args(char *path, t_env *env)
{
	char	*old_path;

	if (!path || !env)
		return;
		
	old_path = NULL;
	if (!ft_strcmp(path, "-"))
	{
		old_path = env_path(env, "OLDPWD");
		if (!old_path)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			return;
		}
		error_chdir(chdir(old_path));
		ft_putstr_fd(old_path, 1);
		ft_putchar_fd('\n', 1);
		free(old_path);
	}
	else if (!ft_strcmp(path, "~"))
	{
		old_path = env_path(env, "HOME");
		if (!old_path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return;
		}
		error_chdir(chdir(old_path));
		free(old_path);
	}
	else if (ft_strcmp(path, ".") && ft_strcmp(path, ".."))
	{
		if (access(path, F_OK) == -1)
			ft_putstr_fd("cd: no such file or directory\n", 2);
		else if (access(path, X_OK) == -1)
			ft_putstr_fd("cd: permission denied\n", 2);
		else
			error_chdir(chdir(path));
	}
	else
		error_chdir(chdir(path));
}

static int	handle_too_many_args(char **paths)
{
	perror("cd: too many arguments");
	free_td(paths);
	return (1);
}

static int	handle_home_cd(t_env *env)
{
	char	*home;

	home = env_path(env, "HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	error_chdir(chdir(home));
	free(home);
	return (0);
}

int	ft_cd(char **args, t_env **env)
{
	if (!args || !*env)
		return (1);
	
	if (!args[1] || !*args[1])  // No argument or empty string
		return (handle_home_cd(*env));
		
	if (args[2] != NULL)
		return (handle_too_many_args(args));
		
	check_cd_args(args[1], *env);
	change_current_path(env);
	free_td(args);
	return (0);
}
