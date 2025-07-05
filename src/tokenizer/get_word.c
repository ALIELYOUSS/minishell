/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:44:49 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/06 00:31:19 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	for_word(char c)
{
	return (c != '<' && c != '>' && c != '&'
		&& c != '|' && c != '(' && c != ')');
}

char	*get_word(char *str, int *index)
{
	char	*word;
	int		j;
	int		i;

	i = *index;
	while (str[i] && !ft_isspace(str[i])
		&& for_word(str[i]) && i < ft_strlen(&str[0]))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (!found_quotes(str, &i))
				return (NULL);
		}
		i++;
	}
	word = malloc(i - *index + 1);
	if (!word)
		return (NULL);
	j = 0;
	while (*index < i)
	{
		word[j] = str[*index];
		j++;
		(*index)++;
	}
	word[j] = '\0';
	return (word);
}
