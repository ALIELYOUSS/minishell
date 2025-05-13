#include "../../inc/minishell.h"

int	for_word(char c)
{
	return (c != '<' && c != '>' && c != '&'
			&& c != '|' && c != '(' && c != ')');
}

void	quotes_syntax_error(char *prompt)
{
	write(2, "Syntax Error 2\n", 15);
	if (prompt)
		free(prompt);
	exit(0);
}

int	quotes_closed(char *content, int *index, char c)
{

	int	i;

	i = *index;
	while (content[++i])
	{
		if (content[i] == c)
			return (1);
	}
	return (0);
}

void	found_quotes(char *content, int *i)
{
	int	tmp;

	tmp = *i;
    if ((content[tmp] == '"' || content[tmp] == '\''))
	{
		if (content[tmp]  == '"') 
		{
			if (quotes_closed(content, &tmp, '"'))
			{
				while (content[++(*i)] && content[*i] != '"')
					;
			}
			else
				quotes_syntax_error(content);
		}
		else if (content[tmp]  == '\'') 
		{
			if (quotes_closed(content, &tmp, '\''))
			{
				while (content[++(*i)] && content[*i] != '\'')
					;
			}
			else
				quotes_syntax_error(content);
		}
	}
}

char	*get_word(char *str, int *index)
{
	char	*word;
	int		j;
	int		i;

	i = *index;
	while (str[i] && !ft_isspace(str[i])
		&& for_word(str[i]) && i < ft_strlen(&str[0]))
	{
		if (str[i] == '"' || str[i] == '\'')
			found_quotes(str, &i);
		i++;
	}
	word = malloc(i - *index + 1);
	if (!word)
		return (NULL);
	j = 0;
	while (*index < i)
	{
		word[j] = str[*index];
		j++;
		(*index)++;
	}
	word[j] = '\0';
	return (word);
}
