/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:24:00 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/05 15:05:48 by alel-you         ###   ########.fr       */
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

int	parenthese_se(t_list *tokens, t_tokens *token, int	*flag)
{
	if (token->type == LP)
	{
		if ((token != tokens->head && (!previous(tokens, token) || prev_node(tokens, token) == RP || prev_node(tokens, token) == WORD)) || !closed_parenthese(token))
		{
			// printf("%d\n", prev_node(tokens, token));
			// printf("return %d\n", previous(tokens, token));
			// printf("here 4\n");
			syntax_error_msg(tokens);
			return (0);
		}
		else if (closed_parenthese(token) == -1)
		{
			(*flag) = 1;
			if (!multi_parenth(tokens, token, flag))
			{
				printf("here 5\n");
				return (0);
			}
		}
		else
			(*flag)++;
	}
	else if (token->type == RP)
	{
		(*flag)--;
		if (*flag == 0 || (token->next && token->next->type == WORD))
		{
			// printf("here 6 \n");
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
		// printf("%d\n", prev_node(tokens, tmp));
		// printf("%d\n", tmp->next->type);
		// printf("%s\n", tmp->content);
		// printf("here 2\n");
		syntax_error_msg(tokens);
		return (0);
	}
	else if (parenthese(tmp))
	{
		if ((tmp == tokens->head && tmp->next == tokens->tail
				&& tmp->type == LP && tmp->next->type == RP)
			|| (tmp->type == LP && tmp->next->type == PIPE))
		{
			// printf("here 3\n");
			syntax_error_msg(tokens);
			return (0);
		}
		if (!parenthese_se(tokens, tmp, &flag))
		{
			// printf("here 10\n");
			return (0);
		}
	}
	return (1);
}

int size_hrdoc(t_tokens	*tokens_list)
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

int	syntax_errors(t_list *tokens)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
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


void	here_doc(t_tokens *token, t_env *env_list, t_hrdoc **hrd_fd)
{
	t_tokens	*tmp;
	int			i;
	
	i = 0;
	tmp = token;
	if (!tmp)
		return ;
	(*hrd_fd)->fd = malloc(sizeof(int) * (*hrd_fd)->size);
	while (tmp)
	{
		if (tmp->next && tmp->type == HRDOC && tmp->next->type == WORD && i < (*hrd_fd)->size)
		{
			(*hrd_fd)->fd[i++] = herdoc_handler(tmp->next->content, env_list);		
			continue ;
		}
		tmp = tmp->next;
	}
}