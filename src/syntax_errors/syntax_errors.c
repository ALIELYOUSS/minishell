/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:24:00 by yael-maa          #+#    #+#             */
/*   Updated: 2025/05/13 19:03:28 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	syntax_errors(t_list *tokens)
{
	t_tokens	*tmp;

	if (operator(tokens->head) || operator(tokens->tail) || is_redir(tokens->tail))
		syntax_error_msg(tokens);
	tmp = tokens->head;
	while (tmp)
	{
		if ((is_redir(tmp) && tmp->next->type != WORD) || (operator(tmp) && operator(tmp->next)))
			syntax_error_msg(tokens);
		tmp = tmp->next;
	}
}
