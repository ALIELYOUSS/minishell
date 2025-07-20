/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 04:07:37 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/10 08:06:45 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*new_env_node(char *key, char *value, int *f)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env), sizeof(t_env));
	if (!new)
		return (write(2, "Memory Error\n", 13), NULL);
	new->key = key;
	new->value = value;
	new->f = *f;
	new->next = NULL;
	return (new);
}

t_env	**add_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!(*env))
	{
		printf("here\n");
		*env = new;
	}
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (env);
}

t_env	*env_dup(t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (!env)
		return (NULL);
	new = NULL;
	new = NULL;
	tmp = env;
	while (tmp)
	{
		add_env(&new, new_env_node(tmp->key, tmp->value, &tmp->f));
		tmp = tmp->next;
	}
	return (new);
}

void	ft_swap(t_env *tmp, t_env *e_tmp)
{
	char	*key_swap;
	char	*value_swap;
	int		f_swap;

	key_swap = tmp->key;
	tmp->key = e_tmp->key;
	e_tmp->key = key_swap;
	value_swap = tmp->value;
	tmp->value = e_tmp->value;
	e_tmp->value = value_swap;
	f_swap = tmp->f;
	tmp->f = e_tmp->f;
	e_tmp->f = f_swap;
}

void	sort_env(t_env **env)
{
	t_env	*tmp;
	t_env	*e_tmp;

	tmp = *env;
	while (tmp)
	{
		e_tmp = tmp->next;
		while (e_tmp)
		{
			if (ft_strcmp(tmp->key, e_tmp->key) > 0)
				ft_swap(tmp, e_tmp);
			e_tmp = e_tmp->next;
		}
		tmp = tmp->next;
	}
}
