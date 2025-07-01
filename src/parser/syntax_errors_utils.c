/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:38:52 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/01 04:49:26 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	syntax_error_msg(t_list *tokens)
{
	if (tokens->head)
		clear_list(tokens);
	write(2, "Syntax Error\n", 13);
	return ;
}

int	parenthese(t_tokens *token)
{
	return (token->type == LP || token->type == RP);
}

int	ispipe(t_tokens *token)
{
	return (token->type == PIPE);
}

int	is_redir(t_tokens *token)
{
	t_type	type;

	type = token->type;
	return (type == OUT || type == IN || type == APP || type == HRDOC);
}

t_type	prev_node(t_list *tokens, t_tokens *token)
{
	t_tokens	*tmp;

	tmp = tokens->head;
	while (tmp && tmp->next != token)
		tmp = tmp->next;
	return (tmp->type);
}
