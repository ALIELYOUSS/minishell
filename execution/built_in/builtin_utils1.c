/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:07:16 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/15 11:27:55 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_valid_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_env_list(t_env *env)
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

void	check_cd_args(char *path, t_env *env)
{
	if (!path || !env)
		return ;
	if (!ft_strcmp(path, "-"))
		handle_cd_dash(env);
	else if (!ft_strcmp(path, "~"))
		handle_cd_tilde(env);
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

void	handle_cd_dash(t_env *env)
{
	char	*old_path;

	old_path = env_path(env, "OLDPWD");
	if (!old_path)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return ;
	}
	error_chdir(chdir(old_path));
	ft_putstr_fd(old_path, 1);
	ft_putchar_fd('\n', 1);
	free(old_path);
}
