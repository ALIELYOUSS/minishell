/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:55:36 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/07 21:04:26 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*add_cmd_to_path(char *path, char *cmd)
{
	char	*path_slash;
	char	*ret;

	path_slash = ft_strjoin(path, "/");
	if (!path_slash)
		return (free(path), NULL);
	ret = ft_strjoin(path_slash, cmd);
	if (!ret)
		return (free(path_slash), NULL);
	free(path_slash);
	return (ret);
}

int	handle_builtin(t_cmd *t_cmd_list, t_env **env)
{
	if (!ft_strncmp(t_cmd_list->cmd, "exit", 4))
		return (ft_exit(t_cmd_list->cmd, *env));
	else if (!ft_strncmp(t_cmd_list->cmd, "pwd", 3))
		return (ft_pwd());
	else if (!ft_strncmp(t_cmd_list->cmd, "env", 3))
		return (ft_env(*env));
	else if (!ft_strncmp(t_cmd_list->cmd, "echo", 4))
		return (handle_echo(t_cmd_list));
	else if (!ft_strncmp(t_cmd_list->cmd, "cd", 2))
		return (ft_cd(t_cmd_list->cmd, env));
	else if (!ft_strncmp(t_cmd_list->cmd, "export", 6))
		return (ft_export(t_cmd_list->cmd, *env));
	else if (!ft_strncmp(t_cmd_list->cmd, "unset", 5))
		return (handle_unset(t_cmd_list->cmd, env));
	return (-1337);
}

static int	process_child_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

void	close_wait(int *pipe_fds, int len, int *children)
{
	int	i;
	int	status;
	int	last_exit_status;

	i = 0;
	last_exit_status = 0;
	while (i < len)
	{
		close(pipe_fds[i]);
		i++;
	}
	free(pipe_fds);
	if (children)
	{
		i = 0;
		while (i < (len / 2) + 1)
		{
			waitpid(children[i], &status, 0);
			last_exit_status = process_child_status(status);
			i++;
		}
		get_exit_status(last_exit_status, SET);
		free(children);
	}
}
