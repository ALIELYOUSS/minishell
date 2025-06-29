/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:01:59 by alel-you          #+#    #+#             */
/*   Updated: 2025/06/29 18:05:12 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	error_chdir(int chdir_return)
{
	if (chdir_return != 0)
		perror("cannot find path");
}

void	ft_cd(char *prompt, t_env *env)
{
	char	*path;
	char	**paths;

	path = NULL;
	paths = ft_split(prompt, ' ');
	if (!paths)
		return ;
	if (paths[2] != NULL)
		perror("cd: too many arguments");
	if ((!path[2] && paths[1] == NULL) || (ft_strncmp(paths[1], "", 1) == 0))
	{
		path = env_path(env, "HOME");
		if (!path)
		{
			perror("HOME NOT SET");
			return ;
		}
		error_chdir(chdir(path));
		free(path);
	}
	else
		error_chdir(chdir(paths[1]));
	free_td(paths);
}
