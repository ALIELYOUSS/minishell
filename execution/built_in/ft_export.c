/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 03:29:19 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/09 02:08:49 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_env(t_env *env, char *s)
{
	t_env	*tmp;

	tmp = env;
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
	while (cmd[i] && (cmd[i] != '+' || (cmd[i] == '+' && cmd[i + 1] && cmd[i + 1] != '=')) 
		&& cmd[i] != '=' && !ft_isspace(cmd[i]))
		i++;
	key = malloc(i++);
	if (!key)
		return (write(2, "Memory Error\n", 13), NULL);
	j = 0;
	while (cmd[j] && (cmd[j] != '+' || (cmd[j] == '+' && cmd[j + 1] && cmd[j + 1] != '=')) && cmd[j] != '=' && !ft_isspace(cmd[j]))
	{
		key[j] = cmd[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}

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

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->key = key;
	node->value = value;
	node->f = f;
	tmp->next = node;
	env = node;
	node->next = NULL;
}

char	*extract_value(char *cmd, int *index)
{
	char	*value;
	int		i;

	while (cmd[*index] && cmd[*index] != '=')
		(*index)++;
	if (cmd[*index + 1] != '=' && !cmd[*index + 2])
		return (NULL);
	i = (*index) + 1;
	while (cmd[i])
		i++;
	value = malloc(i - *index);
	if (!value)
		return (write(2, "Memory Error\n", 13), NULL);
	i = 0;
	while (cmd[++(*index)])
	{
		value[i] = cmd[*index];
		i++;
	}
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
	while (cmd[i] && (cmd[i] != '+' || (cmd[i] == '+' && cmd[i + 1] && cmd[i + 1] != '=')) && cmd[i] != '=' && !ft_isspace(cmd[i]))
		i++;
	if (cmd[i] && cmd[i] == '+')
	{
		f = 1;
		i++;
	}
	if (cmd[i] && cmd[i] == '=')
	{
		value = extract_value(cmd, &i);
		e_tmp = find_var(env, key);
		if (e_tmp && (!e_tmp->value || f == 1))
		{
			e_tmp->value = simple_join(e_tmp->value, value);
			e_tmp->f = 1;
		}
		else if (e_tmp && (!e_tmp->value || f == 0))
		{
			e_tmp->value = value;
			e_tmp->f = 1;
		}
		else
			add_var(env, key, value, 1);
	}
	else
	{
		if (!find_var(env, key))
			add_var(env, key, NULL, -1);
	}
}

int	ft_export(char *cmd, t_env *env, char **arg)
{
	char	*key;
	int		index;
	int		i;

	if (!strncmp(cmd, arg[0], ft_strlen(cmd)))
	{
		print_env(env, "declare -x ");
		return (0);
	}
	index = 6;
	i = 1;
	while (arg[i])
	{
		if (quotes_ps(arg[i]))
			arg[i] = replace_quotes(arg[i]);
		key = retrieve_key(arg[i]);
		if (!key)
		{
			write(2, "Memory Error\n", 13);
			return (0);
		}
		if (!valid_identifier(key))
		{
			printf("bash: export: `%s': not a valid identifier\n", key);
			return (0);
		}
		handle_export_value(arg[i], env, key);
		i++;
	}
	return (0);
}