/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:14:13 by yael-maa          #+#    #+#             */
/*   Updated: 2025/06/26 23:26:53 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	open_file(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->redir && tmp->redir->type != HRDOC)
		{
			if (tmp->redir && tmp->redir->type != HRDOC && tmp->redir->type != APP)
				tmp->redir->fd = open(tmp->redir->file, O_CREAT | O_RDWR, 0777);
			else if (tmp->redir && tmp->redir->type == APP)
				tmp->redir->fd = open(tmp->redir->file, O_CREAT | O_APPEND |O_RDWR, 0777);
		}
		tmp = tmp->next;
	}
}