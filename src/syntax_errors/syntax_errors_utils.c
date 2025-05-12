/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:38:52 by yael-maa          #+#    #+#             */
/*   Updated: 2025/05/08 22:34:33 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	syntax_error_msg(t_list *tokens)
{
    if (tokens->size)
        clear_list(tokens);
    write(2, "Syntax Error\n", 13);
	exit(0);
}

int	find_token(t_tokens *tokens, t_type type)
{
	t_tokens	*tmp;
	
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == type)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

