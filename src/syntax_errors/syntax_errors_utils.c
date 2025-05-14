/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:38:52 by yael-maa          #+#    #+#             */
/*   Updated: 2025/05/14 20:27:41 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	syntax_error_msg(t_list *tokens)
{
	if (tokens->head)
		clear_list(tokens);
	write(2, "Syntax Error 1\n", 15);
	exit(0);
}

int	parenthese(t_tokens *token)
{
 	return (token->type == LP || token->type == RP);
}

int	operator(t_tokens *token)
{
	return (token->type == AND || token->type == OR
		|| token->type == PIPE);
}

int	is_redir(t_tokens *token)
{
	t_type	type;

	type = token->type;
	return (type == OUT || type == IN
		|| type == HRDOC || type == APP);
}

int	its_token(t_tokens *tokens, t_type type)
{
	if (tokens->type == type)
		return (1);
	return (0);
}

int	find_token(t_tokens *tokens, t_type type)
{
	t_tokens	*tmp;
	
	tmp = tokens;
	while (tmp)
	{
		if (its_token(tmp, type))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	prev_node(t_list *tokens, t_tokens *token)
{
	t_tokens	*tmp;
	
	tmp = tokens->head;
	while (tmp && tmp->next != token)
		tmp = tmp->next;
	if (is_redir(tmp))
		return (1);
	return (0);
}