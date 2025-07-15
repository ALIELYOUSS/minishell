/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:14:13 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/15 09:32:58 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	fd_open(char *file_name, int flag)
{
	int	fd;

	fd = 0;
	if (flag == OUT)
	{
		fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (fd < 0)
			return (perror("open >"), 1337);
	}
	else if (flag == APP)
	{
		fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0777);
		if (fd < 0)
			return (perror("open >>"), 1337);

	}
	else if (flag == IN)
	{
		fd = open(file_name, O_RDONLY, 0777);
		if (fd < 0)
			return (perror("open <"), 1337);
	}
	return (fd);
}

int open_file(t_cmd **cmd, t_env *env_list)
{
	t_cmd	*tmp;
	t_redir	*tmp2;

	tmp = *cmd;
	if (!cmd)
	   return (0);
	while (tmp)
	{
		tmp2 = tmp->redir;
		while (tmp2)
		{
			if (tmp2->type == APP || tmp2->type == OUT)
				tmp->out = fd_open(tmp2->file, tmp2->type);
			else if (tmp2->type == IN)
				tmp->in = fd_open(tmp2->file, tmp2->type);
			else if (tmp2->type == HRDOC)
				(*cmd)->hrd = herdoc_handler(tmp2->file, env_list);
			if (tmp->in == 1337 || tmp->out == 1337)
				return (0);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

void	normal_add(t_env *env, char *key)
{
	if (!find_var(env, key))
		add_var(env, key, NULL, -1);
}
