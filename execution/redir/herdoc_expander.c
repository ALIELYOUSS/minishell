/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 22:44:35 by alel-you          #+#    #+#             */
/*   Updated: 2025/06/27 23:05:54 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	here_doc_expansion(char *cmd, char **env)
{
	char	*par_name;
	char	*bef_var;
	char	*par_value;
	char	*expanded;
	int		index;
	int		i;
	int		x;

    x = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			if (cmd[i + 1] == '$')
			{
				expansion_helper(cmd, &i, '$');
				continue ;
			}
			par_name = var_name(cmd, &i, &index);
			bef_var = bef_param(cmd, &i);
			if (!found_var(env, par_name))
				par_value = ft_strdup(" ");
			else
				par_value = var_value(par_name, env);
			expanded = simple_join(bef_var, par_value);
			free(par_value);
			cmd = simple_join(expanded, &cmd[index]);
		}
		i++;
	}
}