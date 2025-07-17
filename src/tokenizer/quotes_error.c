/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:48:14 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/16 02:05:35 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	quotes_syntax_error(char c)
{
	write(2, "minishell: unexpected EOF while looking for matching ", 53);
	write(2, "\'", 1);
	ft_putchar_fd(c, 2);
	write(2, "\'\n", 2);
	return ;
}

int	quotes_closed(char *content, int *index, char c)
{
	int	i;

	i = *index;
	while (content[++i])
	{
		if (content[i] == c)
			return (1);
	}
	return (0);
}

int	found_quotes_helper(char *content, int *i, int *tmp, char c)
{
	if (quotes_closed(content, tmp, c))
	{
		while (content[++(*i)] && content[*i] != c)
			;
	}
	else
	{
		quotes_syntax_error(c);
		return (0);
	}
	return (1);
}

int	found_quotes(char *content, int *i)
{
	int	tmp;

	tmp = *i;
	if ((content[tmp] == '"' || content[tmp] == '\''))
	{
		if (content[tmp] == '"')
		{
			if (!found_quotes_helper(content, i, &tmp, '"'))
				return (0);
		}
		else if (content[tmp] == '\'')
		{
			if (!found_quotes_helper(content, i, &tmp, '\''))
				return (0);
		}
	}
	return (1);
}
