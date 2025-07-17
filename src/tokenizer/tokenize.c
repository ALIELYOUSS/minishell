/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:24:00 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/17 04:45:46 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_qquote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i++;
		else
			return (0);
	}
	return (1);
}

int	word_tokenizer(t_list *tokens, char *content, int *i)
{
	char		*word;
	t_tokens	*token;

	word = get_word(content, i);
	if (!word)
	{
		if (word)
			free(word);
		return (0);
	}
	token = create_token(word, WORD);
	if (!token)
	{
		free(word);
		write(2, "memory Error\n", 13);
		return (0);
	}
	add_node(tokens, token);
	return (1);
}

void	redir_and_hrdc(t_list *tokens, char *content, int *i)
{
	if (content[*i] == '<' && content[*i + 1] != '<')
		add_node(tokens, create_token(ft_strdup("<"), IN));
	else if (content[*i] == '>' && content[*i + 1] != '>')
		add_node(tokens, create_token(ft_strdup(">"), OUT));
	else if (content[*i] == '>' && content[*i + 1] == '>')
	{
		add_node(tokens, create_token(ft_strdup(">>"), APP));
		(*i)++;
	}
	else if (content[*i] == '<' && content[*i + 1] == '<')
	{
		add_node(tokens, create_token(ft_strdup("<<"), HRDOC));
		(*i)++;
	}
}

void	tokenizer_helper(t_list *tokens, char *content, int *i)
{
	if (content[*i] == '<' || content[*i] == '>')
		redir_and_hrdc(tokens, content, i);
	else if (content[*i] == '|')
		add_node(tokens, create_token(ft_strdup("|"), PIPE));
	else if (content[*i] == '(' || content[*i] == ')')
	{
		if (content[*i] == '(')
			add_node(tokens, create_token(ft_strdup("("), LP));
		else
			add_node(tokens, create_token(ft_strdup(")"), RP));
	}
}

int	tokenizer(t_list *tokens, char *content, int *i)
{
	while (content[*i] && *i < ft_strlen(content))
	{
		while (content[*i] && ft_isspace(content[*i]))
			(*i)++;
		if (content[*i] && for_word(content[*i]) && !ft_isspace(content[*i]))
		{
			if (!word_tokenizer(tokens, content, i))
				return (0);
		}
		else if (content[*i] && !for_word(content[*i])
			&& !ft_isspace(content[*i]))
		{
			tokenizer_helper(tokens, content, i);
			(*i)++;
		}
		if (content[*i] == '\0' || *i >= ft_strlen(content))
			break ;
	}
	return (1);
}
