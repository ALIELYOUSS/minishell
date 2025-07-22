/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 04:33:10 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/22 14:40:34 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	rq_strcpy(char *cmd, char *final_cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(cmd))
	{
		if (cmd[i] == -1)
			i++;
		if (cmd[i] && cmd[i] != -1)
		{
			final_cmd[j] = cmd[i];
			j++;
			i++;
		}
	}
	final_cmd[j] = '\0';
}

void	print_env(t_env *env, char *s, int fd)
{
	t_env	*tmp;

	tmp = env;
	sort_env(&tmp);
	while (tmp)
	{
		if (s && tmp->key)
			ft_putstr_fd(s, fd);
		if (tmp->value || tmp->f == 1)
			print_it(tmp->key, tmp->value, fd);
		else if (!tmp->value && tmp->f == 1)
		{
			ft_putstr_fd(tmp->key, fd);
			ft_putchar_fd('\n', fd);
		}
		else if (tmp->key && tmp->f != 1)
		{
			ft_putstr_fd(tmp->key, fd);
			ft_putchar_fd('\n', fd);
		}
		if (tmp)
			tmp = tmp->next;
	}
}

char	*exit_expand(t_cmd **tmp, int *i)
{
	char	*par_value;

	if ((*tmp)->cmd[*i] && (*tmp)->cmd[*i + 1] && (*tmp)->cmd[*i + 1] == '?')
		par_value = ft_itoa(get_exit_status(0, GET));
	else
		return (NULL);
	return (par_value);
}
