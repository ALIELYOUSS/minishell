/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:07:16 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/09 23:18:45 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

int	ft_exit(char *args, t_env *env_list)
{
	char	**splited;

	splited = ft_split(args, ' ');
	if (!splited)
		error_msg("");
	printf("exit\n");
	fflush(stdout);
	if (!splited[1])
		exit(0);
	if (splited[1] && is_digit(splited[1]) == 1 && !splited[2])
	{
		free_env_list(env_list);
		get_exit_status(ft_atoi(splited[1]), SET);
		exit_status(ft_atoi(splited[1]));
	}
	else
		printf("exit: too many argumments\n");
	return (free_td(splited), 0);
}
