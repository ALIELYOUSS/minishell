/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:04:32 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/08 23:31:03 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

char	*bef_param(char *cmd, int *index)
{
	char	*bef;
	int		i;

	bef = malloc((*index) + 1);
	if (!bef)
		return (write(2, "Memory Error\n", 13), NULL);
	i = -1;
	while ((++i) < *index)
		bef[i] = cmd[i];
	bef[i] = '\0';
	return (bef);
}

char	*simple_join(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (write(2, "Memory Error\n", 13), NULL);
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	j = 0;
	while (s2[j])
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	free(s1);
	return (s3);
}

int	count_char(char *s, int *index, char c)
{
	int	count;
	int	i;

	count = 0;
	i = *index;
	while (s[i] && s[i] == c)
	{
		if (s[i])
			count++;
		i++;
	}
	return (count);
}

void	expansion_helper(char *s, int *index, char c)
{
	if (count_char(s, index, c) % 2 != 0)
	{
		while (s[*index] && s[(*index) + 1] == c)
			(*index)++;
	}
	else
	{
		while (s[*index] && s[*index] == c)
			(*index)++;
	}
}

void	expansion(t_cmd *cmd, t_env *env_lst)
{
	t_cmd			*tmp;
	static int		index;
	int				i;

	tmp = cmd;
	while (tmp)
	{
		tmp->f = 0;
		tmp->dq = 0;
		if (tmp->type == CMD)
		{
			i = 0;
			while (tmp->cmd[i])
			{
				if (tmp->dq == 0 && tmp->cmd[i] == '"')
					tmp->dq++;
				else if (tmp->dq == 0 && tmp->cmd[i] == '\'')
					tmp->dq--;
				if ((tmp->cmd[i] == '"' || cmd->cmd[i] == '\'') && tmp->f >= 0)
					tmp->f++;
				else if ((cmd->cmd[i] == '\'' || tmp->cmd[i] == '"')
					&& cmd->f <= 0)
					tmp->f--;
				if (expander(&tmp, &env_lst, &index, &i))
					continue ;
				i++;
			}
		}
		tmp = tmp->next;
	}
}
