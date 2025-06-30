/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 22:44:35 by alel-you          #+#    #+#             */
/*   Updated: 2025/06/30 18:16:02 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		ft_strlen_value(char *str)
{
	int	i;
	int	len;
	
	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '$' && str[i] != '(' && str[i] != ')')
			len++;
		i++;
	}
	return (len);
}

char	*exp_value(char *exp_value)
{
	char	*value;
	int		i;
	int		x;
	int		len;

	x = 0;
	i = 0;
	len = ft_strlen_value(exp_value);
	value = malloc(len + 1);
	if (!value)
		return (NULL);
	while (exp_value && exp_value[i])
	{
		if (exp_value[i] != '$' && exp_value[i] != '(' && exp_value[i] != ')')
			value[x++] = exp_value[i];
		i++;
	}
	value[x] = '\0';
	return (value);
}


char	*here_doc_expansion(char *input, char **env)
{
	char	*key;
	char	*value;
	int		x;

    x = 0;
	key = exp_key(input);
	if (!key)
		return (NULL);
	while (env && env[x])
	{
		if (!ft_strncmp(env[x], key, ft_strlen(key)))
		{
					
		}
		x++;
	}
	return (NULL);
}
