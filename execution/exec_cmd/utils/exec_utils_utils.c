/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:38:02 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/06 18:13:00 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	pipe_counter(t_cmd *list)
{
	t_cmd	*tmp;
	int		count;

	count = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	is_builtin(char *prompt)
{
	if (!ft_strncmp(prompt, "echo", 4))
		return (1);
	if (!ft_strncmp(prompt, "cd", 2))
		return (1);
	if (!ft_strncmp(prompt, "env", 3))
		return (1);
	if (!ft_strncmp(prompt, "exit", 4))
		return (1);
	if (!ft_strncmp(prompt, "export", 6))
		return (1);
	if (!ft_strncmp(prompt, "pwd", 3))
		return (1);
	if (!ft_strncmp(prompt, "unset", 5))
		return (1);
	return (0);
}

char	*path_tester(char **paths, char *cmd)
{
	int		i;
	char	*path_tester;

	i = 0;
	while (paths[i])
	{
		path_tester = add_cmd_to_path(paths[i], cmd);
		if (!path_tester)
			return (free_td(paths), NULL);
		else if (!access(path_tester, X_OK))
			return (free_td(paths), path_tester);
		free(path_tester);
		i++;
	}
	return (NULL);
}

char	*check_current_path(char *cmd)
{
	char	*tmp;

	tmp = cmd;
	if (!ft_strchr(cmd, '/'))
		tmp = ft_strjoin(tmp, "/");
	else if (!access(tmp, X_OK))
		return (tmp);
	else if (ft_strchr(tmp, '/') && access(tmp, X_OK))
		return (error_msg(cmd), free(tmp), NULL);
	free(tmp);
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
			return (free_td(env_paths), path_tester);
		free(path_tester);
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
	path_tester = NULL,
	path_list = env_path(env_list, "PATH");
	if (!path_list)
		return (error_msg(""), NULL);
	paths = ft_split(path_list, ':');
	if (!paths || !paths[0])
		return (free(path_list), NULL);
	free(path_list);
	path_tester = check_path_env(paths, cmd);
	if (path_tester)
		return (path_tester);
	return (free_td(paths), NULL);
}