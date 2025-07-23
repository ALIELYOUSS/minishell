/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:11:21 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/23 18:32:34 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_sig;

void	sig_int(void)
{
	if (g_sig == 0)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
		get_exit_status(130, SET);
	}
}

void	stop_hrdoc(void)
{
	if (g_sig == 2)
	{
		g_sig = 1;
		get_exit_status(127, SET);
		close(0);
	}
}

void	sig_handler(int sig_num)
{
	if (sig_num == SIGINT && g_sig == 0)
		sig_int();
	stop_hrdoc();
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSTOP, SIG_IGN);
}
