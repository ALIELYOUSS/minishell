/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:11:21 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/06 19:09:02 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	sig_handler(int sig_num)
{
	char	*new_line;
	int		std_in;

	new_line = NULL;
	std_in = 0;
	if (sig_num == SIGINT && g_sig != 2)
	{
		if (g_sig == 1)
			write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		get_exit_status(130, SET);
	}
	if (g_sig == 2)
	{
		write(1, "\n", 1);
		g_sig = 1;
		get_exit_status(127, SET);
		close(0);
	}
	if (sig_num == SIGQUIT && g_sig != 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		get_exit_status(131, SET);
	}
}

void	setup_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
