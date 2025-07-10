/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:16:05 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/10 02:30:32 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*splited(char *cmd, int *index)
{
	char	*arg;
	int		i;

	i = 0;
	while (cmd[*index] && ft_isspace(cmd[*index]))
		(*index)++;
	arg = malloc(arg_size(cmd, index));
	if (!arg)
		return (write(2, "Memory error\n", 13), NULL);
	while (cmd[*index] && !ft_isspace(cmd[*index]))
	{
		if (cmd[*index] == '"' || cmd[*index] == '\'')
			quote_case(arg, cmd, index, &i);
		else
			arg[i++] = cmd[(*index)++];
	}
	arg[i] = '\0';
	return (arg);
}

int	arr_size(char *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	check_cmd(cmd, &i, &count);
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

	j = arr_size(cmd);
	arr = malloc(sizeof(char *) * (j + 1));
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

char	*expand_args_helper(char *cmd)
{
	int	index;
	int	i;
	char	*par_name;
	char	*bef_var;
	char	*expanded;
	char	*par_value;

	i = 0;
	while (cmd[i] && cmd[i] != '$' )
		i++;
	if (!cmd[i])
		return (cmd);
	else if (cmd[i] == '$')
	{
		index = 0;
		par_name = var_name(cmd, &i, &index);
		bef_var = bef_param(cmd, &i);
		par_value = ft_strdup("");
		expanded = simple_join(bef_var, par_value);
		cmd = simple_join(expanded, &cmd[index]);
	}
	return (cmd);
}

void	expand_args(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		arr[i] = expand_args_helper(arr[i]);
		i++;
	}
}

void	split_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = (*cmd);
	while (tmp)
	{
		if (tmp->cmd)
		{
			tmp->arg = args(tmp->cmd);
			expand_args(tmp->arg);
		}
		tmp = tmp->next;
	}
}
