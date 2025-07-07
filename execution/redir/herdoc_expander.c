/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 22:44:35 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/07 13:59:09 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*create_expanded_string(char *result, int i, t_env *env)
{
	char	*tmp1;
	char	*tmp2;
	char	*key;
	char	*val;

	tmp1 = ft_substr(result, 0, i);
	tmp2 = ft_strdup(result + (i + ft_find_pos(result + i + 1) + 1));
	key = ft_substr(result, i + 1, ft_find_pos(result + i + 1));
	val = env_path(env, key);
	free(key);
	if (!val)
		return (join_without_val(tmp1, tmp2));
	else
		return (join_with_val(tmp1, tmp2, val));
}

char	*get_key(char *input, t_env *env)
{
	char	*result;
	char	*new_result;
	int		i;

	result = ft_strdup(input);
	i = 0;
	while (result[i])
	{
		if (result[i] == '$' && result[i + 1] != '$')
		{
			new_result = create_expanded_string(result, i, env);
			free(result);
			result = new_result;
			i = 0;
		}
		else
			i++;
	}
	return (result);
}

char	*here_doc_expansion(char *input, t_env *env)
{
	char	*expanded;

	expanded = get_key(input, env);
	return (expanded);
}
