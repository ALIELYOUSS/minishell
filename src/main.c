/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:06:06 by yael-maa          #+#    #+#             */
/*   Updated: 2025/04/25 20:24:32 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	for_word(char c)
{
	return (c != '<' && c != '>' && c != '&'
			&& c != '|' && c != '(' && c != ')');
}

char	*get_word(char *str, int *i)
{
	char	*word;
	int		n;
	int		tmp;

	n = 0;
	tmp = *i;
	while (str[tmp] && !ft_isspace(str[tmp]) && !for_word(str[tmp]))
	{
		tmp++;
		n++;
	}
	word = malloc(n * sizeof(char) + 1);
	if (!word)
		return (NULL);
	n = 0;
	while (str[*i] && !ft_isspace(str[*i]) && !for_word(str[*i]))
		word[n++] = str[(*i)++];
	word[n] = '\0';
	return (word);
}

int	main(int ac, char **av)
{
	char			*prompt;
	t_list			tokens;
	static int		i;

	(void)ac;
	(void)av;
	ft_bzero(&tokens, sizeof(t_list));
	tokens.size = 0;
	while (1)
	{
		prompt = readline("/minishell$");
		if (!finish_prompt(prompt));
			break ;
		i = 0;
		while (prompt[i] && ft_isspace(prompt[i]))
			i++;
		if (prompt[i] && !for_word(prompt[i]))
			add_node(&tokens, create_token(get_word(&prompt[i], i), 1));
	}
	return (0);
}
