/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:26:43 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/10 05:30:14 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	normal_add(t_env *env, char *key)
{
	if (!find_var(env, key))
		add_var(env, key, NULL, -1);
}

void	print_env(t_env *env, char *s)
{
	t_env	*tmp;

	tmp = env; 
	sort_env(&tmp);
	while (tmp)
	{
		if (s)
			printf("%s", s);
		if (tmp->value)
			printf("%s=\"%s\"\n", tmp->key, tmp->value);
		else if (!tmp->value && tmp->f == 1)
			printf("%s=\"\"\n", tmp->key);
		else
			printf("%s\n", tmp->key);
		tmp = tmp->next;
	}
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
