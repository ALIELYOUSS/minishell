/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:24:00 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/15 00:32:57 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int is_qquote(char *str)
{
	int i;

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
	if (!word || !*word)
	{
		printf("1    %s\n", word);
		if (tokens)
			clear_list(tokens);
		return (0);
	}
	else if (is_qquote(word))
	{
		printf("2   %s\n", word);
		free(word);
		if (tokens->size)
			clear_list(tokens);
		write(2, "memory Error\n", 13);
		return (0);
	}
	token = create_token(word, WORD);
	if (!token)
	{
		printf("2   %s\n", word);
		if (tokens->size)
			clear_list(tokens);
		write(2, "memory Error\n", 13);
		return (0);
	}
	printf("3: %s\n", word);
	add_node(tokens, token);
	return (1);
}

void	redir_and_hrdc(t_list *tokens, char *content, int *i)
{
	if (content[*i] == '<' && content[*i + 1] != '<')
		add_node(tokens, create_token("<", IN));
	else if (content[*i] == '>' && content[*i + 1] != '>')
		add_node(tokens, create_token(">", OUT));
	else if (content[*i] == '>' && content[*i + 1] == '>')
	{
		add_node(tokens, create_token(">>", APP));
		(*i)++;
	}
	else if (content[*i] == '<' && content[*i + 1] == '<')
	{
		add_node(tokens, create_token("<<", HRDOC));
		(*i)++;
	}
}

void	tokenizer_helper(t_list *tokens, char *content, int *i)
{
	if (content[*i] == '<' || content[*i] == '>')
		redir_and_hrdc(tokens, content, i);
	else if (content[*i] == '|')
		add_node(tokens, create_token("|", PIPE));
	else if (content[*i] == '(' || content[*i] == ')')
	{
		if (content[*i] == '(')
			add_node(tokens, create_token("(", LP));
		else
			add_node(tokens, create_token(")", RP));
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
