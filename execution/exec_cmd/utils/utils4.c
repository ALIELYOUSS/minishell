/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:21:43 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/22 00:16:44 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*path_tester(char **paths, char *cmd)
{
	int		i;
	char	*path_tester;

	i = 0;
	while (paths[i])
	{
		path_tester = add_cmd_to_path(paths[i], cmd);
		if (!path_tester)
			return (NULL);
		else if (!access(path_tester, X_OK))
			return (path_tester);
		i++;
	}
	return (NULL);
}

char	*check_current_path(char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		cmd = ft_strjoin("./", cmd);
	if (!access(cmd, X_OK))
		return (cmd);
	else
		return (NULL);
}

char	*check_path_env(char **env_paths, char *cmd)
{
	int		i;
	char	*path_tester;

	i = 0;
	path_tester = NULL;
	while (env_paths[i])
	{
		path_tester = add_cmd_to_path(env_paths[i], cmd);
		if (!path_tester)
			return (NULL);
		else if (!access(path_tester, X_OK))
			return (path_tester);
		i++;
	}
	return (NULL);
}

char	*return_path(char *cmd, t_env *env_list)
{
	char	**paths;
	char	*path_list;
	char	*path_tester;
	char	*tmp;

	tmp = check_current_path(cmd);
	if (tmp)
		return (tmp);
	tmp = cmd;
	path_tester = NULL;
	path_list = env_path(env_list, "PATH");
	if (!path_list)
		return (write(1, cmd, ft_strlen(cmd)), error_msg(":"), NULL);
	paths = ft_split(path_list, ':');
	path_tester = check_path_env(paths, cmd);
	if (path_tester)
		return (path_tester);
	return (NULL);
}

void	error_msg(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
