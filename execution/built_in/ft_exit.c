/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:07:16 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/17 05:05:19 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_no_args(t_env *env_list)
{
	free_env_list(env_list);
	get_current_cmd(FREE, NULL);
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
	printf("exit: %s: numeric argument required\n", s);
	free_env_list(env_list);
	get_current_cmd(FREE, NULL);
	exit(2);
}

int	ft_exit(char **args, t_env *env_list)
{
	int		exit_code;
	t_cmd	**current_cmd;

	if (!args)
		return (write(2, "exit: too few arguments\n", 24), 1);
	printf("exit\n");
	fflush(stdout);
	current_cmd = get_current_cmd(GET, NULL);
	if (current_cmd && *current_cmd)
		get_current_cmd(FREE, NULL);
	if (!args[1])
		handle_no_args(env_list);
	if (args[2])
		return (handle_too_many_args());
	if (!is_valid_number(args[1]))
		handle_invalid_number(args[1], env_list);
	exit_code = ft_atoi(args[1]);
	exit_code = (exit_code % 256 + 256) % 256;
	free_env_list(env_list);
	set_pwd_get(FREE, NULL);
	get_exit_status(exit_code, SET);
	get_current_cmd(FREE, NULL);
	leak_killer(NULL, FREE);
	free_td(args);
	exit(exit_code);
}
