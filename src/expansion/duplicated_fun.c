/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicated_fun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:18:52 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/22 12:45:40 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*exit_expand_2(t_redir **tmp, int *i)
{
	char	*par_value;

	if ((*tmp)->file[*i] && (*tmp)->file[*i + 1] && (*tmp)->file[*i + 1] == '?')
		par_value = ft_itoa(get_exit_status(0, GET));
	else
		return (NULL);
	return (par_value);
}

void	non_expanded_change(char **arr)
{
	int		i;
	int		j;
	int		index;
	char	*bef;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == '$')
			{
				index = j;
				bef = bef_param(arr[i], &index);
				// while (arr[i][index] && !ft_isspace(arr[i][index]) && arr[i][index] != '$')
				// 	index++;
				printf("===============||%s\n", bef);
				printf("========= 1 %d", index);
				bef = simple_join(ft_strdup(bef), "");
				printf("========= 2 %d", index);
				// while (arr[i][++j] && !ft_isspace(arr[i][j]) && arr[i][j] != '$')
				// 	;
				arr[i] = simple_join(bef, &arr[i][j + 1]);
			}
			printf("===============%s\n", arr[i]);
			j++;
		}
		i++;
	}
}

void	non_expanded(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = (*cmd);
	while (tmp)
	{
		if (tmp->arg)
			non_expanded_change(tmp->arg);
		tmp = tmp->next;
	}
}