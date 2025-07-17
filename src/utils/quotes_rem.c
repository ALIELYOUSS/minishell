/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_rem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:10:25 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/17 04:58:09 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	quotes_ps(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			return (1);
	}
	return (0);
}

void	flag_quotes_helper(char *cmd, int *index, int *flag, char q)
{
	cmd[*index] = -1;
	(*index)++;
	while (cmd[*index] && cmd[*index] != q)
	{
		if (cmd[(*index)] == '\\')
			(*index)++;
		if (cmd[(*index)])
			(*index)++;
	}
	cmd[(*index)] = -1;
	(*flag) += 2;
	(*index)++;
}

void	flag_quotes(char *cmd, int *flag)
{
	int	i;

	i = 0;
	while (cmd[i] && i < ft_strlen(cmd))
	{
		if (cmd[i] && cmd[i] == '"' && (i == 0 || cmd[i - 1] != '\\'))
			flag_quotes_helper(cmd, &i, flag, '"');
		if (cmd[i] && cmd[i] == '\'' && (i == 0 || cmd[i - 1] != '\\'))
			flag_quotes_helper(cmd, &i, flag, '\'');
		if (cmd[i] && cmd[i] != '"' && cmd[i] != '\'')
			i++;
	}
}

char	*replace_quotes(char *cmd)
{
	int		f;
	char	*final_cmd;

	f = 0;
	flag_quotes(cmd, &f);
	final_cmd = malloc(ft_strlen(cmd) - f + 1);
	if (!final_cmd)
		return (write(2, "Memory Error\n", 13), NULL);
	rq_strcpy(cmd, final_cmd);
	return (final_cmd);
}

void	remove_quotes(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == CMD && quotes_ps(tmp->cmd))
			tmp->cmd = replace_quotes(tmp->cmd);
		tmp = tmp->next;
	}
}
