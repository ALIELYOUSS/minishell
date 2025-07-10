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

static void	handle_no_args(char **splited, t_env *env_list)
{
	free_td(splited);
	free_env_list(env_list);
	exit(0);
}

static int	handle_too_many_args(char **splited)
{
	printf("exit: too many arguments\n");
	get_exit_status(1, SET);
	free_td(splited);
	return (1);
}

static void	handle_invalid_number(char **splited, t_env *env_list)
{
	printf("exit: %s: numeric argument required\n", splited[1]);
	free_td(splited);
	free_env_list(env_list);
	exit(2);
}

int	ft_exit(char *args, t_env *env_list)
{
	char	**splited;
	int		exit_code;
	t_cmd	**current_cmd;

	splited = ft_split(args, ' ');
	if (!splited)
		error_msg("");
	printf("exit\n");
	fflush(stdout);
	current_cmd = get_current_cmd(GET, NULL);
	if (current_cmd && *current_cmd)
		get_current_cmd(FREE, NULL);
	if (!splited[1])
		handle_no_args(splited, env_list);
	if (splited[2])
		return (handle_too_many_args(splited));
	if (!is_valid_number(splited[1]))
		handle_invalid_number(splited, env_list);
	exit_code = ft_atoi(splited[1]);
	exit_code = (exit_code % 256 + 256) % 256;
	free_td(splited);
	free_env_list(env_list);
	get_exit_status(exit_code, SET);
	exit(exit_code);
}
