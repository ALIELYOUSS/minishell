/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:06:06 by yael-maa          #+#    #+#             */
/*   Updated: 2025/05/04 20:52:09 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	print_list(t_list *tokens)
{
	t_tokens	*tmp;

	tmp = tokens->head;
	while (tmp != tokens->tail)
	{
		printf("---------------content------------- :%s\n", tmp->content);
		printf("---------------type------------- :%d\n", tmp->type);
		tmp = tmp->next;
	}
	printf("-------------content------------ :%s\n", tmp->content);
	printf("---------------type------------- :%d\n", tmp->type);
}

int	main(int ac, char **av)
{
	char			*prompt;
	static char			*content;
	char			*word;
	t_list			tokens;
	int				i;


	(void)ac;
	(void)av;
	ft_bzero(&tokens, sizeof(t_list));
	tokens.size = 0;
	while (1)
	{
		prompt = readline("~/minishell$ ✗ ");
		if (!finish_prompt(prompt))
			break ;
		if (!prompt)
			break;
		content = str_trim(prompt);
		free(prompt);
		if ( !content || !*content)
			return (1);
		// printf("%s\n", content);
		i = 0;
		while (content[i] && i < ft_strlen(content))
		{
			while (content[i] && ft_isspace(content[i]))
				i++;
			printf ("exterior i = %d\n", i);
			printf ("content %s\n", content);
			if (content[i] && for_word(content[i]) && !ft_isspace(content[i]))
			{
				word = get_word(content, &i);
				// printf("word : %s\n", word);
				// if (!word)
				// 	break;
				add_node(&tokens, create_token(word, WORD));
				// printf("content :%s\n", tokens.head->content);
				// if (tokens.head->next)
					// printf("***content*** :%s\n", tokens.head->next->content);
				// free(word);
			}
			else if (content[i] && !for_word(content[i]) && !ft_isspace(content[i]))
			{
				if (content[i] == '<' || content[i] == '>')
				{
					if (content[i] == '<' && content[i + 1] != '<')
						add_node(&tokens, create_token("<", IN));
					else if (content[i] == '>' && content[i + 1] != '>')
						add_node(&tokens, create_token(">", OUT));
					else if (content[i] == '>' && content[i + 1] == '>')
						add_node(&tokens, create_token(">>", APP));
					else if (content[i] == '<' && content[i + 1] == '<')
						add_node(&tokens, create_token("<<", HRDOC));
				}
				else if (content[i] == '|')
				{
					if (content[i + 1] == '|')
					{						
						add_node(&tokens, create_token("||", OR));
						i++;
					}
					else
						add_node(&tokens, create_token("|", PIPE));	
				}
				else if (content[i] == '&' && content[i + 1] == '&')
				{
					add_node(&tokens, create_token("&&", AND));
					i++;
				}
				else if (content[i] == '(' || content[i] == ')')
				{
					if (content[i] == '(')
						add_node(&tokens, create_token("(", LP));
					else
						add_node(&tokens, create_token(")", RP));	 
				}
				i++;
			}
			// printf("string : %s\n", &content[i]);
			if (content[i] == '\0' || i >= ft_strlen(content))
				break;
		}
		// printf("%d\n", i);// check the index is gettin to 10 in ls la
	}
	print_list(&tokens);
	return (0);
}

