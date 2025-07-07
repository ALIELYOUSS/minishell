/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:24:00 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/07 02:04:36 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	closed_parenthese(t_tokens *token)
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

int	parenthese_se(t_list *tokens, t_tokens *token, int	*flag)
{
	if (token->type == LP)
	{
		if (!left_p(&token, &tokens, flag))
			return (0);
	}
	else if (token->type == RP)
	{
		(*flag)--;
		if (*flag == 0 || (token->next && token->next->type == WORD))
		{
			syntax_error_msg(tokens);
			return (0);
		}
	}
	return (1);
}

int	syntax_errors_helper(t_list *tokens, t_tokens *tmp)
{
	int			flag;

	flag = 0;
	if ((is_redir(tmp) && tmp->next->type != WORD) || (ispipe(tmp)
			&& ispipe(tmp->next)) || (ispipe(tmp)
			&& (ispipe(tmp->next) || tmp->next->type == RP)))
	{
		syntax_error_msg(tokens);
		return (0);
	}
	else if (parenthese(tmp))
	{
		if ((tmp == tokens->head && tmp->next == tokens->tail
				&& tmp->type == LP && tmp->next->type == RP)
			|| (tmp->type == LP && tmp->next->type == PIPE))
		{
			syntax_error_msg(tokens);
			return (0);
		}
		if (!parenthese_se(tokens, tmp, &flag))
			return (0);
	}
	return (1);
}

int	syntax_errors(t_list *tokens)
{
	t_tokens	*tmp;

	tmp = NULL;
	if (ispipe(tokens->head) || ispipe(tokens->tail)
		|| is_redir(tokens->tail) || tokens->head->type == RP
		|| tokens->tail->type == LP)
	{
		syntax_error_msg(tokens);
		return (0);
	}
	tmp = tokens->head;
	while (tmp)
	{
		if (!syntax_errors_helper(tokens, tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
