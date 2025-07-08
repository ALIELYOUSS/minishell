/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:16:05 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/08 04:41:12 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	loop_quote(char *cmd, int *index, char c)
{
	if (cmd[*index + 1])
		(*index)++;
	while (cmd[*index] && cmd[*index] != c)
		(*index)++;
	return (*index);
}
//lllllls la ""7
int	arg_size(char *cmd, int *index)
{
	int	i;

	i = *index;
	if (cmd[i] == "\"" || cmd[i] == "\'")
	{
		if (cmd[i] == "\"")
			return (loop_quote(cmd, &i, "\"") - *index + 1);
		else if (cmd[i] == "\'")
			return (loop_quote(cmd, &i, "\'") - *index + 1);
	}
	while (cmd[i] && !ft_isspace(cmd[i]))
		(i)++;
	return (i - *index + 1);
}

char	*splited(char *cmd, int *index)
{
	char	*arg;
	int		i;

	while (cmd[*index] && ft_isspace(cmd[*index]))
		(*index)++;
	arg = malloc(arg_size(cmd, index));
	if (!arg)
		return (write (2, "Memory error\n", 13), NULL);
	i = 0;
	while (cmd[*index] && !ft_isspace(cmd[*index]))
	{
		if (cmd[*index] == "\'" || cmd[*index] == "\"")
		{
			while (cmd[*index] && cmd[*index] != "\"" && cmd[*index] != "\'")
			{
				arg[i] = cmd[*index];
				i++;
				(*index)++;
			}
		}
		
		(*index)++;
	}
}

void	split_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;
	char	**arg;
	int		i;

	tmp = (*cmd);
	while (tmp)
	{
		i = -1;
		while (tmp->cmd[++i])
		{
			
		}
	    tmp = tmp->next;
	}
}