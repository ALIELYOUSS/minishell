/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:38:02 by alel-you          #+#    #+#             */
/*   Updated: 2025/06/29 17:48:01 by alel-you         ###   ########.fr       */
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
	else if (!ft_strncmp(prompt, "cd", 2))
		return (1);
	else if (!ft_strncmp(prompt, "env", 3))
		return (1);
	else if (!ft_strncmp(prompt, "exit", 4))
		return (1);
	else if (!ft_strncmp(prompt, "export", 6))
		return (1);
	else if (!ft_strncmp(prompt, "pwd", 3))
		return (1);
	else if (!ft_strncmp(prompt, "unset", 5))
		return (1);
	return (0);
}

char	*return_path(char *cmd, t_env *env_list)
{
	char	**paths;
	char	*path_list;
	char	*path_tester;
	int		i;

	i = 0;
	path_tester = NULL;
	path_list = env_path(env_list, "PATH");
	if (!path_list)
		error_msg("");
	paths = ft_split(path_list, ':');
	if (!paths || !paths[0])
		return (NULL);
	while (paths[i])
	{
		path_tester = add_cmd_to_path(paths[i], cmd);
		if (!path_tester)
			return (NULL);
		else if (!access(path_tester, X_OK))
		{
			free_td(paths);
			return (path_tester);
		}
		free(path_tester);
		i++;
	}
	perror("command not found");
	free_td(paths);
	return (NULL);
}
