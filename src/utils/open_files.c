/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:14:13 by yael-maa          #+#    #+#             */
/*   Updated: 2025/06/28 23:03:51 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	open_file(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir *tmp2;
	tmp = cmd;
	while (tmp)
	{
		tmp2 = tmp->redir;
		while (tmp2)
		{
			if (tmp2->type == OUT || tmp2->type == APP)
			{	
				tmp2->fd = open(tmp2->file, O_CREAT | O_RDWR, 0777);
				tmp->out = tmp2->fd;
			}	
			else
			{
				tmp2->fd = open(tmp2->file, O_CREAT | O_APPEND |O_RDWR, 0777);
			}
			
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}