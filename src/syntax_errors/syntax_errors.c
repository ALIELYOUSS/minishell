/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:24:00 by yael-maa          #+#    #+#             */
/*   Updated: 2025/05/20 19:05:02 by yael-maa         ###   ########.fr       */
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

int	multi_parenth(t_list *tokens, t_tokens *token, int *flag)
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
	{
		syntax_error_msg(tokens);
		return (0);
	}
	return (1);
}

int	parenthese_se(t_list *tokens, t_tokens *token, int	*flag)
{
	if (token->type == LP)
	{
		if (!closed_parenthese(token))
		{
			syntax_error_msg(tokens);
			return (0);
		}
		else if (closed_parenthese(token) == -1)
		{
			(*flag) = 1;
			if (!multi_parenth(tokens, token, flag))
				return (0);
		}
		else
			(*flag)++;
	}
	else if (token->type == RP)
	{
		if (*flag == 0)
		{
			syntax_error_msg(tokens);
			return (0);
		}
	}
	return (1);
}

void	syntax_errors(t_list *tokens)
{
	t_tokens	*tmp;
	int			flag;

	// tmp = tokens->tail;
	if (operator(tokens->head) || operator(tokens->tail) || is_redir(tokens->tail) || tokens->head->type == RP
		|| tokens->tail->type == LP)
	{
		syntax_error_msg(tokens);
		return ;
	}
	tmp = tokens->head;
	flag = 0;
	while (tmp)
	{
		if ((is_redir(tmp) && tmp->next->type != WORD) || (operator(tmp) && operator(tmp->next)) || (tmp->type == PIPE && (operator(tmp->next) || tmp->next->type == RP)) )
		{
			syntax_error_msg(tokens);
			return ;
		}
		else if (parenthese(tmp))
		{
			if ((tmp == tokens->head && tmp->next == tokens->tail && tmp->type == LP && tmp->next->type == RP) || (tmp->type == LP && tmp->next->type == PIPE))
			{
				syntax_error_msg(tokens);
				return ;	
			}
			if (!parenthese_se(tokens, tmp, &flag))
				return ;
			// flag = 2;
		}
		tmp = tmp->next;
	}
}
