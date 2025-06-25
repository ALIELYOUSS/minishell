/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:32:14 by alel-you          #+#    #+#             */
/*   Updated: 2024/12/03 18:06:04 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_joing_data(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		x;
	int		len;

	i = 0;
	x = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	joined = malloc(sizeof(char) * (len + 1));
	if (!joined)
		return (NULL);
	while (s1 && s1[i])
		joined[x++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		joined[x++] = s2[i++];
	joined[x] = '\0';
	free(s1);
	return (joined);
}

static char	*ft_read_from_fd(char *rest, int fd)
{
	int		readed_bytes;
	char	*tmp;

	readed_bytes = 1;
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (free(rest), NULL);
	while (readed_bytes > 0)
	{
		readed_bytes = read(fd, tmp, BUFFER_SIZE);
		if (readed_bytes == -1)
			return (free(tmp), free(rest), NULL);
		if (readed_bytes == 0)
			break ;
		tmp[readed_bytes] = '\0';
		rest = ft_joing_data(rest, tmp);
		if (ft_strchr(rest, '\n'))
			break ;
	}
	free(tmp);
	return (rest);
}

static char	*ft_extrct_shift(char **rest)
{
	char	*line;
	char	*tmp;

	tmp = *rest;
	line = ft_getline(tmp);
	if (!line)
		return (free(*rest), *rest = NULL, NULL);
	*rest = ft_get_rest(tmp);
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	rest = ft_read_from_fd(rest, fd);
	if (!rest)
		return (NULL);
	line = ft_extrct_shift(&rest);
	if (!line)
		return (NULL);
	return (line);
}
