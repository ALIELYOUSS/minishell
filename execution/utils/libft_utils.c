#include "../../inc/minishell.h"


size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	if (dstsize <= 0)
		return (ft_strlen(src));
	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (dstsize <= dest_len)
		return (dstsize + src_len);
	while (src[i] && dest_len + i < dstsize - 1)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	slen;

	i = 0;
	slen = ft_strlen(src);
	if (!dstsize)
		return (slen);
	while (i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (slen);
}

static int	ft_check_len(char *s1, char *s2)
{
	int	lenght;

	lenght = ft_strlen(s1) + ft_strlen(s2) + 1;
	return (lenght);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		lenght;

	if (!s1 || !s2)
		return (NULL);
	lenght = ft_check_len(s1, s2);
	join = malloc(lenght);
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	ft_strlcat(join, s2, lenght);
	return (join);
}


static int	ft_words_count(char *s, char c)
{
	int	i;
	int	count;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && s[i] && s[i + 1] == c)
			count++;
		else if (s[i] != c && s[i + 1] == '\0')
			count++;
		i++;
	}
	return (count);
}

static int	ft_lenght(char *s, char c)
{
	int	i;
	int	len;

	if (!s)
		return (0);
	i = 0;
	len = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		if (s[i] != c)
			len++;
		i++;
	}
	return (len);
}

static char	**ft_free(char **word, unsigned int i)
{
	while (i--)
		free(word[i]);
	free(word);
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	t_var	p;

	p.i = 0;
	p.len = 0;
	p.n = 0;
	p.words = ft_words_count(s, c);
	p.sp = (char **)malloc(sizeof(char *) * (p.words + 1));
	if (!p.sp)
		return (NULL);
	while (p.i < p.words)
	{
		p.x = 0;
		p.len = ft_lenght(s + p.n, c);
		p.sp[p.i] = (char *)malloc(p.len + 1);
		if (!p.sp[p.i])
			return (ft_free(p.sp, p.i));
		while (s[p.n] && s[p.n] == c)
			p.n++;
		while (s[p.n] && s[p.n] != c)
			p.sp[p.i][p.x++] = s[p.n++];
		p.sp[p.i][p.x] = '\0';
		p.i++;
	}
	p.sp[p.i] = (NULL);
	return (p.sp);
}

char	*ft_strchr( char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s && fd >= 0)
	{
		write(fd, s, ft_strlen(s));
	}
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len >= ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start];
		start++;
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
}

int	ft_strcmp( char *s1,  char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static long	ft_absolut(int a)
{
	long	tmp;

	tmp = a;
	if (tmp < 0)
	{
		tmp = -tmp;
		return (tmp);
	}
	return (tmp);
}

static int	ft_a_len(int a)
{
	long	tmp;
	int		len;

	tmp = 0;
	len = 0;
	if (a < 0)
	{
		len++;
		tmp = ft_absolut(a);
	}
	else
		tmp = a;
	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int a)
{
	int		len;
	char	*str;
	long	tmp;

	if (a == -0)
		return (ft_strdup("0"));
	len = ft_a_len(a);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	if (a < 0)
		tmp = ft_absolut(a);
	else
		tmp = a;
	while (len >= 0)
	{
		str[len] = (tmp % 10) + '0';
		tmp /= 10;
		len--;
	}
	if (a < 0)
		str[0] = '-';
	return (str);
}

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	tmp;

	i = 0;
	sign = 1;
	tmp = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = (tmp * 10) + (str[i] - '0');
		i++;
	}
	tmp *= sign;
	return (tmp);
}