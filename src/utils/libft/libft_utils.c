#include "../../../inc/minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

t_tokens	*create_token(void *content, int t)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->type = t;
	return (new);
}

void	add_node(t_list *tokens, t_tokens *token)
{
	if (!tokens || !token)
		return ;
	if (tokens->size == 0)
	{
		tokens->head = token;
		tokens->tail = token;
		tokens->size++;
		return ;
	}
	tokens->tail->next = token;
	tokens->tail = token;
	tokens->size++;

}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*c;
	size_t			i;

	c = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		c[i] = 0;
		i++;
	}
}

char	*join_it(char *s1, char *s2, char c, int *index)
{
	char	*s3;
	int		len;
	int		i;

	i = 0;
	while (s2[i] && s2[i] != c)
		i++;
	if (s2[i] == '\0')
		len = ft_strlen(s1) + i + 1;
	else
		len = ft_strlen(s1) + i + 2;
	s3 = malloc(len);
	if (!s3)
		return (NULL);
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[++(*index)] != c && s2[(*index)])
		s3[i] = s2[*index];
	s3[i] = c;
	if (c != '\0')
		s3[i] = '\0';
	free(s1);
	return (s3);
}
