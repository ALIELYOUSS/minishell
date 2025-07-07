/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:14:13 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/07 20:57:25 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	fd_open(char *file_name, int flag)
{
	int fd;

	fd = 0;
	if (flag == OUT)
	{
		fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (fd < 0)
			perror("open >");
	}
	else if (flag == APP)
	{
		fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0777);
		if (fd < 0)
			perror("open >>");
	}
	else if (flag == IN)
	{
		fd = open(file_name, O_RDONLY, 0777);
		if (fd < 0)
			perror("open <");
	}
	return (fd);
}

void	open_file(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_redir	*tmp2;

	tmp = *cmd;
	while (tmp)
	{
		tmp2 = tmp->redir;
		while (tmp2)
		{
			if (tmp2->type == APP || tmp2->type == OUT)
				tmp->out = fd_open(tmp2->file, tmp2->type);
			else if (tmp2->type == IN)
				tmp->in =  fd_open(tmp2->file, tmp2->type);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}
