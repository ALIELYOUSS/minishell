#include "../../inc/minishell.h"

int	for_word(char c)
{
	return (c != '<' && c != '>' && c != '&'
			&& c != '|' && c != '(' && c != ')');
}

void	syntax_error(char *prompt)
{
	write(2, "Syntax Error\n", 13);
	if (prompt)
		free(prompt);
	exit(0);
}

int	quotes_closed(char *content,int *index, char c)
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
			if (quotes_closed(&content[tmp], &tmp, '"'))
			{
				while (content[++(*i)] && content[*i] != '"')
					;
			}
			else
				syntax_error(content);
		}
		else if (content[tmp]  == '\'') 
		{
			if (quotes_closed(&content[tmp], &tmp, '\''))
			{
				while (content[++(*i)] && content[*i] != '\'')
					;
			}
			else
				syntax_error(content);
		}
	}
}


char	*get_word(char *str, int *index)
{
	char    *word;
	int		j;
	int		i;

	// printf("here\n");
	// while (!ft_isspace(str[*index]))
	while (str[*index] && ft_isspace(str[*index]))
		(*index)++;
	i = *index;
	// printf("%c || %d || %d || total : %d\n", str[i], i, *index, i - *index + 2);
	printf("ee%cee\n", str[*index]);
	while (str[i] && !ft_isspace(str[i]) && for_word(str[i]) && i < ft_strlen(&str[0]))
	{
		// printf("%d || %d || total : %d\n", i, *index, i - *index + 2);
		if (str[i] == '"' || str[i] == '\'')
			found_quotes(str, &i);
		// printf("%c____\n", str[i]);
		printf("-------  here  %d %d--------x------\n", *index, i);
		i++;//ls la
	}
	word = malloc(i - *index + 1);
	if (!word)
		return (NULL);
	j = 0;
	printf("-------  here  %d %d--------------\n", *index, i);
	while (*index <= i)
	{
		word[j] = str[*index];
		j++;
		printf("-------    %d %d--------------\n", *index, i);
		(*index)++;
	}
	printf("-------    %d %d--------------\n", *index, i);
	printf("-------i = %d--------------\n", i);
	(*index)++;//the problem is after space 
	word[j] = '\0';
	//printf("word : %s\n", word);
	//printf("%d || %d || total : %d\n", i, *index, i - *index + 2);
	return (word);
}
