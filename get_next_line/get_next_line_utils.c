/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:47:49 by alel-you          #+#    #+#             */
/*   Updated: 2025/06/17 23:30:53 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_getline(char *rest)
{
	char	*line;
	int		i;
	int		count;

	i = 0;
	line = NULL;
	count = 0;
	if (!rest || !rest[i])
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[i] && rest[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	while (count < i)
	{
		line[count] = rest[count];
		count++;
	}
	line[count] = '\0';
	return (line);
}

char	*ft_get_rest(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (ft_strdup(str + i));
}
