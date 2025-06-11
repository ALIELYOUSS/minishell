/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:04:32 by yael-maa          #+#    #+#             */
/*   Updated: 2025/06/11 16:23:17 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*var_name(char *content, int *index)
{
	char	*var_name;
	int		i;

	i = *index;
	while (content[i] && !ft_isspace(content[i]))
		i++;
	var_name = malloc(i + 1);
	if (!var_name)
		return (write(2, "Memory Error\n", 13), NULL);
	i = 0;
	while (content[*index] && !ft_isspace(content[*index]))
	{
		var_name[i] = content[*index];
		i++;
		(*index)++;
	}
	var_name[i] = '\0';
	return (var_name);
}

char	*var_value(char *var_name, char **env)
{
	char	*var_value;
	int		i;
	int		j;
	int		len;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(var_name, env[i], (size_t)ft_strlen(var_name) - 1))
		{
			if (env[i][ft_strlen(var_name)] && env[i][ft_strlen(var_name)] == '=')
			{
				var_value = malloc(ft_strlen(env[i]) - ft_strlen(var_name));
				if (!var_value)
					return (write(2, "Memory Error\n", 13), NULL);
				len = ft_strlen(var_name) + 1;
				j = 0;
				while (env[i][len])
				{
					var_value[j] = env[i][len];
					len++;
					j++;
				}
				var_value[j] = '\0';
				break ;
			}
		}
		i++;
	}
	return (var_value);
}

void	expand(t_cmd *cmd, char **env)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			i = 0;
			while (tmp->cmd[i])
			{
				if (tmp->cmd[i] == '$')
				{
					i++;
					// change tmp->cmd
					
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
}
