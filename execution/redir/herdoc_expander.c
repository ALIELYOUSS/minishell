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
	int i = -1;

	while (s[++i])
	{
		if (s[i] == ' ' || char_state(s[i]) == 2)
			return i;
	}
	return ft_strlen(s);
}

char	*get_key(char *input,t_env *env)
{
	int i;
	char *val;
	char *tmp1;
	char *tmp2;
	

	i = -1;
	while (input[++i])
	{
		if (input[i] == '$' && input[i + 1] != '$')
		{
			tmp1 = ft_substr(input, 0, i);
			tmp2 = ft_strdup(input + (i + ft_find_pos(input + i + 1) + 1));
			val = env_path(env, ft_substr(input, i + 1, ft_find_pos(input + i + 1)));
			if (!val)
			{
				input = ft_strjoin(tmp1, tmp2);
			}
			else
			{
				input = ft_strjoin(tmp1, val);
				free(val);
				input = ft_strjoin(input, tmp2);
				free(tmp2);
				i += ft_strlen(val + 1);
			}
		}
	}
	return(input);
}

char	*here_doc_expansion(char *input, t_env *env)
{
	char	*value;

	value = get_key(input, env);
	return (value);
}

