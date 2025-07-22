/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:13:05 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/22 16:51:38 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_printable(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (1);
		i++;
	}
	return (-1);
}

int	ft_env(t_env *env, int fd)
{
	t_env	*current;

	current = env;
	if (!env)
		return (1);
	while (current)
	{
		if (current->value)
			print_it(current->key, current->value, fd);
		current = current->next;
	}
	return (0);
}

int	handle_env(char **args, t_env *env_list, int fd)
{
	if (args && args[1])
	{
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(":  No such file or directory\n", 2);
		return (127);
	}
	return (ft_env(env_list, fd));
}
