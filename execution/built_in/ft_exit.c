/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:07:16 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/21 23:51:03 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_no_args(t_env *env_list)
{
	(void)env_list;
	get_garbage_head(NULL, FREE);
	exit(0);
}

static int	handle_too_many_args(void)
{
	printf("exit: too many arguments\n");
	get_exit_status(1, SET);
	return (1);
}

static void	handle_invalid_number(char *s, t_env *env_list)
{
	(void)env_list;
	printf("exit: %s: numeric argument required\n", s);
	get_garbage_head(NULL, FREE);
	exit(2);
}

int	ft_exit(char **args, t_env *env_list)
{
	int		exit_code;

	if (!args)
		return (write(2, "exit: too few arguments\n", 24), 1);
	printf("exit\n");
	fflush(stdout);
	if (!args[1])
		handle_no_args(env_list);
	if (args[2])
		return (handle_too_many_args());
	if (!is_valid_number(args[1]))
		handle_invalid_number(args[1], env_list);
	exit_code = ft_atoi(args[1]);
	exit_code = (exit_code % 256 + 256) % 256;
	get_exit_status(exit_code, SET);
	clear_all(FREE);
	exit(exit_code);
}
