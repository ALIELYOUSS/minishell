/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:26:43 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/13 22:34:28 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	key = malloc(i + 1);
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

static void	print_it(char *key, char *value, int fd)
{
	ft_putstr_fd(key, fd);
	ft_putchar_fd('=', fd);
	ft_putchar_fd('\"', fd);
	ft_putstr_fd(value, fd);
	ft_putchar_fd('\"', fd);
	ft_putchar_fd('\n', fd);
}

void	print_env(t_env *env, char *s, int fd)
{
	t_env	*tmp;

	tmp = env;
	sort_env(&tmp);
	while (tmp)
	{
		if (s)
			ft_putstr_fd(s, fd);
		if (tmp->value)
			print_it(tmp->key, tmp->value, fd);
		else if (!tmp->value && tmp->f == 1)
		{
			ft_putstr_fd(tmp->key, fd);
			ft_putchar_fd('\n', fd);
		}
		else
		{
			ft_putstr_fd(tmp->key, fd);
			ft_putchar_fd('\n', fd);
		}
		tmp = tmp->next;
	}
}
