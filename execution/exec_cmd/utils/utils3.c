/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:38:02 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/07 01:40:44 by alel-you         ###   ########.fr       */
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

int	is_type(t_cmd *cmd_list, t_type to_find)
{
	t_cmd	*tmp;

	tmp = cmd_list;
	while (tmp)
	{
		if (tmp->redir && tmp->redir->type == to_find)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
