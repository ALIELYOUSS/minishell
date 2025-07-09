/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:21:10 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/09 19:28:49 by yael-maa         ###   ########.fr       */
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

int	arg_size(char *cmd, int *index)
{
	int		i;
	int		size;
	char	quote;

	i = *index;
	size = 0;
	while (cmd[i] && ft_isspace(cmd[i]))
		i++;
	while (cmd[i] && !ft_isspace(cmd[i]))
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			quote = cmd[i++];
			size++;
			while (cmd[i] && cmd[i] != quote)
				increment_helper(&i, &size);
			if (cmd[i] == quote)
				increment_helper(&i, &size);
		}
		else
			increment_helper(&i, &size);
	}
	return (size + 1);
}

int	check_cmd(char *cmd, int *i, int *count)
{
	if (!cmd || !*cmd)
		return (0);
	if (!ft_isspace(cmd[*i]))
		(*count)++;
	return (1);
}
