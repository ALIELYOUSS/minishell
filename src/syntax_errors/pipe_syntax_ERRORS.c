/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_syntax_ERRORS.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:10:29 by yael-maa          #+#    #+#             */
/*   Updated: 2025/05/12 14:34:20 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pipe_se(t_list *tokens, t_tokens *token)
{
	return (token != tokens->head && prev_node(tokens, token) && !operator(token->next));
}