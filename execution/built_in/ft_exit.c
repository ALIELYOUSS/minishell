/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:07:16 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/23 17:59:16 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_no_args(void)
{
	clear_all(EXIT);
	exit(get_exit_status(0, GET));
}

static int	handle_too_many_args(void)
{
	printf("exit: too many arguments\n");
	clear_all(EXIT);
	return (1);
}

static void	handle_invalid_number(char *s)
{
	printf("exit: %s: numeric argument required\n", s);
	clear_all(EXIT);
	exit(2);
}

int	ft_exit(char **args)
{
	int		exit_code;

	if (!args)
		return (write(2, "exit: too few arguments\n", 24), 1);
	printf("exit\n");
	fflush(stdout);
	if (!args[1])
		handle_no_args();
	if (args[2])
		return (handle_too_many_args());
	if (!is_valid_number(args[1]))
		handle_invalid_number(args[1]);
	exit_code = ft_atoi(args[1]);
	exit_code = (exit_code % 256 + 256) % 256;
	get_exit_status(exit_code, SET);
	clear_all(EXIT);
	exit(exit_code);
}
