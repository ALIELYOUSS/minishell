/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:26:43 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/17 04:55:32 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	valid_identifier2(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '=')
		return (0);
	if (arg[i] == '"')
	{
		while (arg[i] && ft_isspace(arg[i]))
			i++;
		while (arg[i] && !ft_isspace(arg[i]) && arg[i] != '=')
			i++;
		if (arg[i] && ft_isspace(arg[i]))
			return (0);
	}
	return (1);
}

int	valid_identifier(char *key)
{
	int	i;

	i = -1;
	while (key[++i])
	{
		if ((i == 0 && (key[i] >= '0' && key[i] <= '9'))
			|| ((key[i] < 'a' || key[i] > 'z')
				&& (key[i] < 'A' || key[i] > 'Z')
				&& (key[i] < '0' || key[i] > '9') && key[i] != '_'))
			return (0);
	}
	return (1);
}

char	*retrieve_key(char *cmd)
{
	char	*key;
	int		i;
	int		j;

	i = 0;
	while (cmd[i] && (cmd[i] != '+'
			|| (cmd[i] == '+' && cmd[i + 1] && cmd[i + 1] != '='))
		&& cmd[i] != '=' && !ft_isspace(cmd[i]))
		i++;
	key = ft_malloc(i + 1, i + 1);
	if (!key)
		return (write(2, "Memory Error\n", 13), NULL);
	j = 0;
	while (j < i)
	{
		key[j] = cmd[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}

void	handle_export_value_helper(char *cmd, int *i, int *f)
{
	while (cmd[*i] && (cmd[*i] != '+' || (cmd[*i] == '+' && cmd[*i + 1]
				&& cmd[*i + 1] != '=')) && cmd[*i] != '='
		&& !ft_isspace(cmd[*i]))
		(*i)++;
	if (cmd[*i] && cmd[*i] == '+')
	{
		*f = 1;
		(*i)++;
	}
}

void	print_it(char *key, char *value, int fd)
{
	ft_putstr_fd(key, fd);
	ft_putchar_fd('=', fd);
	ft_putchar_fd('\"', fd);
	ft_putstr_fd(value, fd);
	ft_putchar_fd('\"', fd);
	ft_putchar_fd('\n', fd);
}
