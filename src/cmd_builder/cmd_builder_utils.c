/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:45:09 by yael-maa          #+#    #+#             */
/*   Updated: 2025/05/22 02:00:31 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd   *lst_last(t_cmd **cmd)
{
    t_cmd   *tmp;

    if (!cmd || !(*cmd))
        return (NULL);
    tmp = *cmd;
    while (tmp)
        tmp = tmp->next;
    return (tmp);
}

t_cmd   *new_cmd(char *content, t_redir *redir,t_type type)
{
    t_cmd   *new;

    new = malloc(sizeof(t_cmd));
    if (!new)
        return (NULL);
    new->cmd = content;
    new->redir = redir;
    new->next = NULL;
}

void    add_cmd(t_cmd **cmd, t_cmd *new)
{
    t_cmd   *tmp;

    if (!cmd || !new)
        return ;
    if (!(*cmd))
        *cmd = new;
    else
    {
        tmp = lst_last(cmd);
        tmp->next = new;
    }
}