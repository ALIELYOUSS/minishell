/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hrd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 22:44:35 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/07 14:04:35 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	char_state(char c)
{
	if (c >= 'a' && c <= 'z')
		return (0);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c == '$' || c == '(' || c == ')'
		|| c == '\'' || c == '"')
		return (2);
	return (3);
}

int	ft_find_pos(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || char_state(s[i]) == 2)
			return (i);
		i++;
	}
	return (ft_strlen(s));
}

char	*join_without_val(char *tmp1, char *tmp2)
{
	char	*result;

	result = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (result);
}

char	*join_with_val(char *tmp1, char *tmp2, char *val)
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
