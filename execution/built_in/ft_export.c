/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 03:29:19 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/18 00:39:41 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*find_var(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_var(t_env *env, char *key, char *value, int f)
{
	t_env	*tmp;
	t_env	*node;

	if (!env || !key || !is_valid_identifier(key))
	{
		ft_help_free(key, value);
		return ;
	}
	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	node = malloc(sizeof(t_env));
	if (!node)
	{
		ft_help_free(key, value);
		return ;
	}
	node->key = key;
	node->value = value;
	node->f = f;
	node->next = NULL;
	tmp->next = node;
}

char	*extract_value(char *cmd, int *index)
{
	char	*value;
	int		i;

	while (cmd[*index] && cmd[*index] != '=')
		(*index)++;
	if (!cmd[*index + 1])
		return (NULL);
	i = *index + 1;
	while (cmd[i])
		i++;
	value = malloc(i - *index);
	if (!value)
		return (write(2, "Memory Error\n", 13), NULL);
	i = 0;
	while (cmd[++(*index)])
		value[i++] = cmd[*index];
	value[i] = '\0';
	return (value);
}

static void	handle_export_value(char *cmd, t_env *env, char *key)
{
	t_env	*e_tmp;
	char	*value;
	int		f;
	int		i;

	f = 0;
	i = 0;
	handle_export_value_helper(cmd, &i, &f);
	if (cmd[i] && cmd[i] == '=')
	{
		value = extract_value(cmd, &i);
		e_tmp = find_var(env, key);
		if (e_tmp && (!e_tmp->value || f == 1))
			new_value(e_tmp, value, 1);
		else if (e_tmp && (!e_tmp->value || f == 0))
			new_value(e_tmp, value, 0);
		else
			add_var(env, key, value, 1);
	}
	else
		normal_add(env, key);
}

int	ft_export(char *cmd, t_env *env, char **arg, int fd)
{
	char	*key;
	int		i;

	if (!strncmp(cmd, arg[0], ft_strlen(cmd)))
		return (print_env(env, "declare -x ", fd), 0);
	i = 1;
	while (arg[i])
	{
		if (!export_quoting(arg, &i))
			continue ;
		key = retrieve_key(arg[i]);
		if (!key)
			return (write(2, "Memory Error\n", 13) - 13);
		if (!invalid_key_msg(key, &i))
		{
			free(key);
			continue ;
		}
		handle_export_value(arg[i], env, key);
		if (arg[i])
			i++;
	}
	return (0);
}
