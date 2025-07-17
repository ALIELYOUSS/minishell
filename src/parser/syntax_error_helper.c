/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 01:55:52 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/17 00:20:53 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	var_value_helper(t_cmd **tmp, int *i, char *par_name, char *par_value)
// {
// 	if ((*tmp)->cmd[*i] && (*tmp)->cmd[*i + 1]
// 		&& (*tmp)->cmd[*i + 1] == '?')
// 		par_value = ft_itoa(get_exit_status(0, GET));
// 	else
// 	{
// 		if (par_name)
// 			free(par_name);
// 		return (0);
// 	}
// 	return (1);
// }

int	size_hrdoc(t_tokens	*tokens_list)
{
	t_tokens	*tmp;
	int			count;

	count = 0;
	tmp = tokens_list;
	while (tmp)
	{
		if (tmp->next && tmp->type == HRDOC && tmp->next->type == WORD)
			count++;
		tmp = tmp->next;
	}
	return (count);
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

int	previous(t_list *tokens, t_tokens *token)
{
	return (prev_node(tokens, token) != LP || prev_node(tokens, token) != PIPE);
}

int	left_p(t_tokens **token, t_list **tokens, int *flag)
{
	if ((*token != (*tokens)->head && (!previous(*tokens, *token)
				|| prev_node(*tokens, *token) == RP
				|| prev_node(*tokens, *token) == WORD))
		|| !closed_parenthese(*token))
	{
		syntax_error_msg(*tokens);
		return (0);
	}
	else if (closed_parenthese(*token) == -1)
	{
		(*flag) = 1;
		if (!multi_parenth(*tokens, *token, flag))
			return (0);
	}
	else
		(*flag)++;
	return (1);
}
