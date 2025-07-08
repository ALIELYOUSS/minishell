/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 03:29:19 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/07 23:24:15 by yael-maa         ###   ########.fr       */
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

char	*retrieve_key(char *cmd, int *index)
{
	char	*key;
	int		i;

	while (cmd[*index] && ft_isspace(cmd[*index]))
		(*index)++;
	i = *index;
	while (cmd[i] && (cmd[i] != '+' || (cmd[i] == '+' && cmd[i + 1] && cmd[i + 1] != '=' && cmd[i + 1] != '=')) 
		&& cmd[i] != '=' && !ft_isspace(cmd[i]))
		i++;
	if (cmd[i] && cmd[i] == '+' && cmd[i + 1] && cmd[i + 1] != '=' && cmd[i + 1] != '=')
		i++;
	key = malloc(i - *index + 1);
	if (!key)
		return (write(2, "Memory Error\n", 13), NULL);
	i = 0;
	while (cmd[*index] && cmd[*index] != '+' && cmd[*index] != '=' && !ft_isspace(cmd[*index]))
	{
		key[i] = cmd[*index];
		(*index)++;
		i++;
	}
	if (cmd[i] && cmd[i] == '+' && cmd[i + 1] && cmd[i + 1] != '=')
		i++;
	key[i] = '\0';
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
	while (cmd[i] && !ft_isspace(cmd[i]))
		i++;
	value = malloc(i - *index);
	if (!value)
		return (write(2, "Memory Error\n", 13), NULL);
	i = 0;
	while (cmd[++(*index)] && !ft_isspace(cmd[*index]))
	{
		value[i] = cmd[*index];
		i++;
	}
	value[i] = '\0';
	return (value);
}

static void	handle_export_value(char *cmd, int *index, t_env *env, char *key)
{
	t_env	*e_tmp;
	char	*value;
	int		f;

	f = 0;
	if (cmd[*index] && cmd[*index] == '+')
	{
		f = 1;
		(*index)++;
	}
	if (cmd[*index] && cmd[*index] == '=')
	{
		value = extract_value(cmd, index);
		e_tmp = find_var(env, key);
		if (e_tmp && (!e_tmp->value || f == 1))
		{
			e_tmp->value = simple_join(e_tmp->value, value);
			e_tmp->f = 1;
		}
		else if (e_tmp && (!e_tmp->value || f == 0))
			e_tmp->value = value;
		else
			add_var(env, key, value, 1);
	}
	else
		add_var(env, key, NULL, -1);
}

static void	handle_recursive_export(char *cmd, int index, t_env *env)
{
	if (cmd[index] && cmd[index] == ' ')
	{
		while (ft_isspace(cmd[index]))
			index++;
		if (cmd[index])
			ft_export(join_it("export", &cmd[index]), env);
	}
}

int	ft_export(char *cmd, t_env *env)
{
	char	*key;
	int		index;

	if (!strncmp(cmd, "export", ft_strlen(cmd)))
	{
		print_env(env, "declare -x ");
		return (0);
	}
	index = 6;
	key = retrieve_key(cmd, &index);
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
	if (!find_var(env, key))
		handle_export_value(cmd, &index, env, key);
	handle_recursive_export(cmd, index, env);
	return (0);
}