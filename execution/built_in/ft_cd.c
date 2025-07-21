/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:01:59 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/21 21:54:16 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error_chdir(int chdir_return)
{
	if (chdir_return != 0)
		perror("");
}

void	handle_cd_tilde(t_env *env)
{
	char	*home;

	home = env_path(env, "HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return ;
	}
	error_chdir(chdir(home));
}

static int	handle_too_many_args(char **paths)
{
	(void)paths;
	perror("cd: too many arguments");
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
	return (0);
}

int	ft_cd(char **args, t_env **env)
{
	if (!args || !*env)
		return (1);
	if (!args[1] || !*args[1])
		return (handle_home_cd(*env));
	if (args[2] != NULL)
		return (handle_too_many_args(args));
	check_cd_args(args[1], *env);
	change_current_path(env);
	return (0);
}
