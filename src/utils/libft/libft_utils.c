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
	new->content = ft_strdup(content);
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
		s3[i++] = s2[*index];
	if (s2[*index] && !ft_isspace(s2[*index]))
		s3[i++] = c;
	s3[i] = '\0';
	free(s1);
	return (s3);
}

char	*str_trim(char *str)
{
	char	*trimed;
	int		start;
	int		end;
	int		i;

	start = 0;
	while (str[start] && ft_isspace(str[start]))
		start++;
	end = ft_strlen(str) - 1;
	while (end >= start && ft_isspace(str[end]))
		end--;
	trimed = malloc (end - start + 2);
	if (!trimed)
		return (NULL);
	i = 0;
	while (start <= end)
		trimed[i++] = str[start++];
	trimed[i] = '\0';
	return (trimed);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}