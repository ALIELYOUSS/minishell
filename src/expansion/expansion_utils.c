/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:08:41 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/14 18:29:28 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*var_name(char *content, int *index, int *end)
{
	char	*var_name;
	int		i;
	int		j;

	i = *index + 1;
	while (content[i] && !ft_isspace(content[i])
		&& content[i] != '"' && content[i] != '\'' && content[i] != '$')
		i++;
	var_name = malloc(i + 1);
	if (!var_name)
		return (write(2, "Memory Error\n", 13), NULL);
	i = 0;
	j = *index + 1;
	while (content[j] && !ft_isspace(content[j])
		&& content[j] != '"' && content[j] != '\'' && content[j] != '$')
	{
		var_name[i] = content[j];
		i++;
		j++;
	}
	(*end) = j;
	var_name[i] = '\0';
	return (var_name);
}

int	found_var(t_env *env, char *var_name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!strcmp(tmp->key, var_name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	expander_helper(t_cmd **tmp, t_env **env_lst, int *index, int *i)
{
	char	*par_name;
	char	*bef_var;
	char	*par_value;
	char	*expanded;

	par_name = var_name((*tmp)->cmd, i, index);
	if ((*tmp)->f >= 0)
	{
		bef_var = bef_param((*tmp)->cmd, i);
		if (!found_var(*env_lst, par_name))
		{
			if (ft_strchr((*tmp)->cmd, '?'))
				par_value = ft_itoa(get_exit_status(0, GET));
			else
			{
				if (par_name)
					free(par_name);
				if (bef_var)
					free(bef_var);
				return ;
			}
		}
		else
			par_value = var_value(par_name, *env_lst);
		expanded = simple_join(bef_var, par_value);
		(*tmp)->cmd = simple_join(expanded, &((*tmp)->cmd[*index]));
	}
	if (par_name)
		free(par_name);
}

int	expander(t_cmd **tmp, t_env **env_lst, int *index, int *i)
{
	if ((*tmp)->cmd[*i] == '$')
	{
		if ((*tmp)->cmd[*i + 1] == '$')
		{
			expansion_helper((*tmp)->cmd, i, '$');
			return (1);
		}
		expander_helper(tmp, env_lst, index, i);
	}
	if ((*tmp)->f == -2 || (*tmp)->f == 2)
		(*tmp)->f = 0;
	return (0);
}
