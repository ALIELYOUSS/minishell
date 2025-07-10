/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:38:02 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/09 15:12:31 by alel-you         ###   ########.fr       */
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

int	get_exit_status(int exit_st, int flg)
{
	static int	value;

	if (flg == SET)
		value = exit_st;
	return (value);
}

t_cmd	**get_current_cmd(int flag, t_cmd **cmd)
{
	static t_cmd	*current_cmd;

	if (flag == SET && cmd)
		current_cmd = *cmd;
	else if (flag == GET)
		return (&current_cmd);
	else if (flag == FREE && current_cmd)
	{
		clear_cmd(current_cmd);
		current_cmd = NULL;
	}
	return (&current_cmd);
}

t_hrdoc	**set_get_hrd(int flag, t_hrdoc **hrd_fds)
{
	static t_hrdoc	*fds;

	if (hrd_fds && *hrd_fds && flag == SET)
		fds = *hrd_fds;
	else if (flag == FREE && *hrd_fds)
	{
		if ((*hrd_fds)->fd)
			free((*hrd_fds)->fd);
	}
	return (&fds);
}
