/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:13:05 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/13 22:37:59 by alel-you         ###   ########.fr       */
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

static void	print_it(char *key, char *value, int fd)
{
	ft_putstr_fd(key, fd);
	ft_putchar_fd('=', fd);
	ft_putstr_fd(value, fd);
	ft_putchar_fd('\n', fd);
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
