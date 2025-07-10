/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:55:36 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/10 20:06:38 by alel-you         ###   ########.fr       */
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
	char	**args;

	args = ft_split(t_cmd_list->cmd, ' ');
	if (!args)
		return (1);
	if (!ft_strcmp(args[0], "exit"))
		return (free_td(args), ft_exit(t_cmd_list->cmd, *env));
	else if (!ft_strcmp(args[0], "pwd"))
		return (free_td(args), ft_pwd());
	else if (!ft_strcmp(args[0], "env"))
		return (free_td(args), ft_env(*env));
	else if (!ft_strcmp(args[0], "echo"))
		return (free_td(args), handle_echo(t_cmd_list));
	else if (!ft_strcmp(args[0], "cd"))
		return (free_td(args), ft_cd(t_cmd_list->cmd, env));
	else if (!ft_strcmp(args[0], "export"))
		return (free_td(args), ft_export(t_cmd_list->cmd, *env,
				t_cmd_list->arg));
	else if (!ft_strcmp(args[0], "unset"))
		return (free_td(args), handle_unset(t_cmd_list->cmd, env));
	ft_putstr_fd(args[0], 1);
	ft_putstr_fd(": command not found\n", 1);
	return (free_td(args), 127);
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
