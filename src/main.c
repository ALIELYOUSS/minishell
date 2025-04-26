/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:06:06 by yael-maa          #+#    #+#             */
/*   Updated: 2025/04/26 21:43:49 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	for_word(char c)
{
	return (c != '<' && c != '>' && c != '&'
			&& c != '|' && c != '(' && c != ')');
}

char	*get_word(char *str, int *i, char c)
{
	char	*word;
	int		n;
	int		tmp;

	n = 0;
	tmp = *i;
	while (str[tmp] != c && !ft_isspace(str[tmp]) && !for_word(str[tmp]))
	{
		tmp++;
		n++;
	}
	word = malloc(n * sizeof(char) + 1);
	if (!word)
		return (NULL);
	n = 0;
	while (str[*i] != c && !ft_isspace(str[*i]) && !for_word(str[*i]))
		word[n++] = str[(*i)++];
	word[n] = c;
	return (word);
}

int	quotes_closed(char *prompt, int *i)
{
	int	tmp;

	tmp = (*i) + 1;
	while (prompt[tmp] || prompt[tmp] != '"' || prompt[tmp] != '\'')
	{
		if (prompt[tmp] != '"' || prompt[tmp] != '\'')
			return (1);
		tmp++;
	}
	return (0);
}

void	garbage_collector(t_list *tokens)
{
	t_tokens	*tmp;
	
	while (tokens->head)
	{
		tmp = tokens->head;
		tokens->head = tokens->head->next;
		free(tmp->content);
		free(tmp);
	}
}

void	syntax_error(t_list *tokens, char *prompt)
{
	write(2, "Syntax Error\n", 13);
	garbage_collector(tokens);
	if (prompt)
		free(prompt);
	exit(0);
}

void	found_quotes(t_list *tokens, char *prompt, int *i)
{
	static char	c;

	if (!ft_isspace(prompt[(*i) - 1]))
	{	
		if (prompt[*i] == '"')
			tokens->tail->content = join_it(tokens->tail->content, prompt, '"', i);
		else if (prompt[*i] == '\'')
			tokens->tail->content = join_it(tokens->tail->content, prompt, '\'', i);
	}
	else
	{
		if (prompt[*i] == '"')
			add_node(tokens, create_token(get_word(prompt, i, '"'), 1));
		else if (prompt[*i] == '\'')
			add_node(tokens, create_token(get_word(prompt, i, '\''), 1));
	}
	if (prompt[(*i) + 1] && !ft_isspace(prompt[(*i) + 1]) && for_word(prompt[(*i) + 1]))
	{
		(*i)++;
		delimiter(&prompt[*i], &c);
		tokens->tail->content = join_it(tokens->tail->content, &prompt[*i], c, i);
	}
}

int	delimiter(char *str, char *c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) || !for_word(str[i]) || str[i] == '"' || str[i] == '\'')
		{
			*c = str[i];
			return (0);
		}
		i++;
	}
	if (str[i] == '\0')
	{
		*c = '\0';	
		return (0);
	}
	return (1);
}

void	quotes_parse(t_list *tokens, char *prompt, int *i)
{
	if (prompt[*i] == '"' || prompt[*i] == '\'')
	{	
		if (!quotes_closed(prompt, i))
			syntax_error(tokens, prompt);
		else
			found_quotes(tokens, prompt, i);
	}
}

void	print_list(t_list *tokens)
{
	t_tokens	*tmp;

	tmp = tokens->head;
	while (tmp)
	{
		printf("content : %s\n", tmp->content);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av)
{
	char			*prompt;
	t_list			tokens;
	static int		i;
	char			c;

	(void)ac;
	(void)av;
	ft_bzero(&tokens, sizeof(t_list));
	tokens.size = 0;
	while (1)
	{
		prompt = readline("~/minishell$");
		if (!finish_prompt(prompt))
			break ;
		i = 0;
		while (prompt[i] && ft_isspace(prompt[i]))
			i++;
		if (prompt[i] && for_word(prompt[i]))
		{
			delimiter(prompt[i], &c);
			add_node(&tokens, create_token(get_word(&prompt[i], &i, c), 1));
		}
		while (prompt[i] && ft_isspace(prompt[i]))
			i++;
		if (prompt[i] && (!for_word(prompt[i]) || prompt[i] == '"' || prompt[i] == '\''))
		{
			quotes_parse(&tokens, &prompt[i], &i);
		}
		print_list(&tokens);
	}
	return (0);
}
