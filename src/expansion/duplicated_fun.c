/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicated_fun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:18:52 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/22 14:39:53 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*exit_expand_2(t_redir **tmp, int *i)
{
	char	*par_value;

	if ((*tmp)->file[*i] && (*tmp)->file[*i + 1] && (*tmp)->file[*i + 1] == '?')
		par_value = ft_itoa(get_exit_status(0, GET));
	else
		return (NULL);
	return (par_value);
}

void	expander_helper_2(t_redir **tmp, t_env **env_lst, int *index, int *i)
{
	char	*par_name;
	char	*bef_var;
	char	*par_value;

	par_name = var_name((*tmp)->file, i, index);
	if ((*tmp)->f >= 0)
	{
		bef_var = bef_param((*tmp)->file, i);
		if (!found_var(*env_lst, par_name))
		{
			par_value = exit_expand_2(tmp, i);
			if (!par_value)
				return ;
		}
		else
			par_value = var_value(par_name, *env_lst);
		(*tmp)->file = simple_join(simple_join(bef_var, par_value),
				&((*tmp)->file[*index]));
	}
}

int	expander_2(t_redir **tmp, t_env **env_lst, int *index, int *i)
{
	if ((*tmp)->file[*i] == '$')
	{
		if ((*tmp)->file[*i + 1] == '$')
		{
			expansion_helper((*tmp)->file, i, '$');
			return (1);
		}
		expander_helper_2(tmp, env_lst, index, i);
	}
	if ((*tmp)->f == -2 || (*tmp)->f == 2)
		(*tmp)->f = 0;
	return (0);
}

void	expand_files(t_cmd **tmp, t_env **env_lst, int *f_index)
{
	t_redir	*e_tmp;
	int		i;

	e_tmp = (*tmp)->redir;
	e_tmp->f = 0;
	while (e_tmp)
	{
		i = 0;
		while (e_tmp->file[i])
		{
			if (e_tmp->file[i] == '"' )
				e_tmp->f++;
			else if ((e_tmp->file[i] == '\'')
				&& e_tmp->f <= 0)
				e_tmp->f--;
			expander_2(&e_tmp, env_lst, f_index, &i);
			if (e_tmp->file[i])
				i++;
		}
		e_tmp = e_tmp->next;
	}
}

void	expand_norm(t_cmd **tmp, t_env **env_lst, int *index)
{
	int	i;

	(*tmp)->f = 0;
	i = 0;
	while ((*tmp)->cmd[i])
	{
		if ((*tmp)->cmd[i] == '"' )
			(*tmp)->f++;
		else if (((*tmp)->cmd[i] == '\'')
			&& (*tmp)->f <= 0)
			(*tmp)->f--;
		expander(tmp, env_lst, index, &i);
		if ((*tmp)->cmd[i])
			i++;
	}
}
