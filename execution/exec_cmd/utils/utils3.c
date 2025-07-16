/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:55:36 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/16 06:47:44 by yael-maa         ###   ########.fr       */
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

static int	handle_command_not_found(char **args)
{
	if (!args || !args[0])
		return (127);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_td(args);
	return (127);
}

int	handle_builtin(t_cmd *t_cmd_list, t_env **env)
{
	char	**args;
	int		fd;

	fd = t_cmd_list->out;
	if (fd < 0)
		fd = 1;
	args = ft_split(t_cmd_list->cmd, ' ');
	if (!args)
		return (1);
	if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args, *env));
	else if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd(args, fd));
	else if (!ft_strcmp(args[0], "env"))
		return (handle_env(args, *env, fd));
	else if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args, fd));
	else if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args, env));
	else if (!ft_strcmp(args[0], "export"))
		return (free_td(args),
			ft_export(t_cmd_list->cmd, *env, t_cmd_list->arg, fd));
	else if (!ft_strcmp(args[0], "unset"))
		return (handle_unset(args, env));
	return (handle_command_not_found(args));
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
