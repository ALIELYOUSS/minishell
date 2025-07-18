/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:41:21 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/18 01:22:33 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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
	free(str);
	return (trimed);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	size_t	len;
	size_t	i;

	s2 = NULL;
	len = 0;
	i = 0;
	if (s1)
	{
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
	}
	return (s2);
}

int	var_len(char *str, int *len)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (*len == i)
		return (1);
	return (0);
}

char	*var_value(char *var_name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, var_name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	**ft_freearr(char **arr)
{
	size_t	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
	arr = NULL;
	return (NULL);
}
