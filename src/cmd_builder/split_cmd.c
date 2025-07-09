/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:16:05 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/09 14:38:40 by yael-maa         ###   ########.fr       */
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
	int	i;
	int	size = 0;
	char	quote;

	i = *index;
	while (cmd[i] && ft_isspace(cmd[i]))
		i++;

	while (cmd[i] && !ft_isspace(cmd[i]))
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			quote = cmd[i++];
			size++; // opening quote
			while (cmd[i] && cmd[i] != quote)
			{
				i++;
				size++;
			}
			if (cmd[i] == quote)
			{
				i++;
				size++; // closing quote
			}
		}
		else
		{
			i++;
			size++;
		}
	}
	return (size + 1); // +1 for null terminator
}

// int	arg_size(char *cmd, int *index)
// {
// 	int	i;

// 	i = *index;
// 	if (cmd[i] == '"' || cmd[i] == '\'')
// 	{
// 		if (cmd[i] == '"')
// 			return (loop_quote(cmd, &i, '"') - *index + 1);
// 		else if (cmd[i] == '\'')
// 			return (loop_quote(cmd, &i, '\'') - *index + 1);
// 	}
// 	while (cmd[i] && !ft_isspace(cmd[i]))
// 		(i)++;
// 	return (i - *index + 1);
// }

// char	*splited(char *cmd, int *index)
// {
// 	char	*arg;
// 	int		i;

// 	while (cmd[*index] && ft_isspace(cmd[*index]))
// 		(*index)++;
// 	arg = malloc(arg_size(cmd, index) + 1);
// 	if (!arg)
// 		return (write (2, "Memory error\n", 13), NULL);
// 	i = 0;
// 	while (cmd[*index] && !ft_isspace(cmd[*index]))
// 	{
// 		if (cmd[*index] == '"' || cmd[*index] == '\'')
// 		{
// 			while (cmd[*index] && cmd[*index] != '"' && cmd[*index] != '\'')
// 			{
// 				arg[i] = cmd[*index];
// 				i++;
// 				(*index)++;
// 			}
// 		}
// 		if (cmd[*index] && !ft_isspace(cmd[*index]))
// 		{
// 			arg[i] = cmd[*index];
// 			(*index)++;
// 			i++;
// 		}
// 	}
// 	arg[i] = '\0';
// 	return (arg);
// }

char	*splited(char *cmd, int *index)
{
	char	*arg;
	int		i = 0;
	char	quote;
	while (cmd[*index] && ft_isspace(cmd[*index]))
		(*index)++;
	arg = malloc(arg_size(cmd, index));
	if (!arg)
		return (write(2, "Memory error\n", 13), NULL);
	while (cmd[*index] && !ft_isspace(cmd[*index]))
	{
		if (cmd[*index] == '"' || cmd[*index] == '\'')
		{
			quote = cmd[*index];
			arg[i++] = cmd[(*index)++];
			while (cmd[*index] && cmd[*index] != quote)
				arg[i++] = cmd[(*index)++];
			if (cmd[*index] == quote)
				arg[i++] = cmd[(*index)++];
		}
		else
		{
			arg[i++] = cmd[(*index)++];
		}
	}
	arg[i] = '\0';
	return (arg);
}

// int	arr_size(char *cmd)
// {
// 	int	count;
// 	int	i;

// 	i = 0;
// 	count = 0;
// 	if (!ft_isspace(cmd[i]))
// 		count++;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '"')
// 		{
// 			loop_quote(cmd, &i, '"');
// 			i++;
// 		}
// 		else if (cmd[i] == '\'')
// 		{
// 			loop_quote(cmd, &i, '\'');
// 			i++;
// 		}
// 		if (cmd[i] && ft_isspace(cmd[i]) && cmd[i + 1] && !ft_isspace(cmd[i + 1]))//cmd[i] && ft_isspace(cmd[i]) && !ft_isspace(cmd[i + 1])
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

int	arr_size(char *cmd)
{
	int	count = 0;
	int	i = 0;

	if (!cmd || !*cmd)
		return (0);
	if (!ft_isspace(cmd[i]))
		count++;
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			i = loop_quote(cmd, &i, cmd[i]);
			if (cmd[i])
				i++;
		}
		else if (ft_isspace(cmd[i]) && cmd[i + 1] && !ft_isspace(cmd[i + 1]))
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

char	**args(char *cmd)
{
	char	**arr;
	int		i;
	int		j;

	arr = malloc(sizeof(char *) * (arr_size(cmd) + 1));
	if (!arr)
		return (write(2, "Memory Error\n", 13), NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		arr[j] = splited(cmd, &i);
		j++;
		if (!cmd[i])
			break ;
		else
			i++;
	}
	arr[j] = NULL;
	return (arr);
}

void	split_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = (*cmd);
	while (tmp)
	{
		tmp->arg = args(tmp->cmd);
	 	tmp = tmp->next;
	}
}