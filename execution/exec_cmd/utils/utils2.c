/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:51:58 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/22 00:21:49 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	add_exit_status(t_env **env, int exit_status)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->key)
		{
			if (!ft_strcmp(tmp->key, "?"))
			{
				tmp->value = ft_itoa(exit_status);
				break ;
			}
		}
		tmp = tmp->next;
	}
}

void	close_all(void)
{
	int	i;

	i = 2;
	while (i++ < 1337)
	{
		if (close(i) == -1)
			break ;
	}
}

void	clear_all(int flag)
{
	if (flag == FREE)
	{
		close_all();
		set_pwd_get(FREE, NULL);
		get_garbage_head(NULL, FREE);
	}
}

void	help_exec_command(char *cmd, t_env *env_list, char **env)
{
	char	**command;
	char	*cmd_path;

	if (!cmd || !cmd[0])
		return (ft_putstr_fd(" :command not found\n", 2));
	cmd_path = NULL;
	command = ft_split(cmd, ' ');
	abs_path(command, env);
	cmd_path = return_path(command[0], env_list);
	if (!cmd_path)
	{
		exec_error_case(cmd, FREE);
		exit(get_exit_status(127, SET));
	}
	execve(cmd_path, command, env);
	exec_error_case(cmd, FREE);
	exit(get_exit_status(127, SET));
}
