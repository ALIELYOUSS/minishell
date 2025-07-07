/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 22:44:35 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/01 23:26:03 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	char_state(char c)
{
	if (c >= 'a' && c <= 'z')
		return (0);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c == '$' || c == '(' || c == ')' \
		|| c == '\'' || c == '"')
		return (2);
	return (3);
}

int ft_find_pos(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || char_state(s[i]) == 2)
			return (i);
		i++;
	}
	return (ft_strlen(s));
}

static char	*join_without_val(char *tmp1, char *tmp2)
{
	char	*result;

	result = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (result);
}

static char	*join_with_val(char *tmp1, char *tmp2, char *val)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(tmp1, val);
	result = ft_strjoin(temp, tmp2);
	free(temp);
	free(val);
	free(tmp1);
	free(tmp2);
	return (result);
}

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

