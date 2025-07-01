/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 22:44:35 by alel-you          #+#    #+#             */
/*   Updated: 2025/06/30 20:21:09 by alel-you         ###   ########.fr       */
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
		|| c == '\'')
		return (2);
	return (3);
}

int		ft_strlen_value(char *str)
{
	int	i;
	int	len;
	
	len = 0;
	i = 0;
	while (str && str[i])
	{
		if (char_state(str[i]) != 2 && char_state(str[i]) == 1)
			len++;
		i++;
	}
	return (len);
}



int	is_upper(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] < 'A' && str[i] > 'Z' && str[i] != '?')
			return (0);
		i++;
	}
	return (1);
}

char	*get_key(char *input)
{
	char	**splited_input;
	char	*tmp_input;
	int		i;

	i = 0;
	tmp_input = NULL;
	splited_input = ft_split(input, ' ');
	if (!splited_input)
		return (0);
	while (splited_input[i])
	{
		if (ft_strchr(splited_input[i], '$') && is_upper(splited_input[i] + 1))
		{
			tmp_input = ft_strdup(splited_input[i] + 1);
			free_td(splited_input);
			return (tmp_input);
		}
		i++;
	}
	return (NULL);
}

char	*parse_key(char *key)
{
	char	*new_key;
	int		i;
	int		x;
	
	i = 0;
	x = 0;
	new_key = malloc(ft_strlen_value(key));
	if (!new_key)
		return (NULL);
	while (key && key[i])
	{
		if (char_state(key[i]) == 1)
			new_key[x++] = key[i];
		else
			return (NULL);
		i++;
	}
	return (new_key);
}

char	*here_doc_expansion(char *input, t_env *env)
{
	char	*key;
	char	*key_finder;

	key = get_key(input);
	if (!key)
		return (NULL);
	key = parse_key(key);
	if (!key)
		return (NULL);
	key_finder = env_path(env, key);
	free(key);
	return (key_finder);
}

