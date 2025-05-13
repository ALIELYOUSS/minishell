/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:24:00 by yael-maa          #+#    #+#             */
/*   Updated: 2025/05/13 20:36:23 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		closed_parenthese(t_tokens *token)
{
	t_tokens	*tmp;

	tmp = token->next;
	while (tmp)
	{
		if (tmp->type == RP)
			return (1);
		if (tmp->type == LP)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

void	multi_parenth(t_list *tokens, t_tokens *token, int *flag)
{
	t_tokens	*tmp;

	tmp = token->next;
	while (tmp)
	{
		if (tmp->type == LP)
			(*flag)++;
		else if (tmp->type == RP)
			(*flag)--;
		tmp = tmp->next;
	}
	if (*flag != 0)
		syntax_error_msg(tokens);
}

void	parenthese_se(t_list *tokens, t_tokens *token, int	*flag)
{
	if (token->type == LP)
	{
		if (!closed_parenthese(token))
			syntax_error_msg(tokens);
		else if (closed_parenthese(token) == -1)
		{
			(*flag)++;
			multi_parenth(tokens, token, flag);
		}
	}
}

void	syntax_errors(t_list *tokens)
{
	t_tokens	*tmp;
	int			flag;

	if (operator(tokens->head) || operator(tokens->tail) || is_redir(tokens->tail))
	{
		printf("1\n");	
		syntax_error_msg(tokens);
	}
	tmp = tokens->head;
	while (tmp)
	{
		if (parenthese(tmp))
		{
			flag = 0;
			parenthese_se(tokens, tmp, &flag);
		}
		if ((is_redir(tmp) && tmp->next->type != WORD) || (operator(tmp) && operator(tmp->next)))
		{
			printf("2\n");
			syntax_error_msg(tokens);
		}	
		tmp = tmp->next;
	}
}
