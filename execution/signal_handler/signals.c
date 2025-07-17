/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:11:21 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/17 22:40:28 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sig_int(void)
{
	if (g_sig != 2)
	{
		rl_on_new_line();
		rl_replace_line("\n", 0);
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

void	sig_stp(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handler(int sig_num)
{
	if (sig_num == SIGINT && g_sig != 2)
	{
		sig_int();
		return ;
	}
	if (sig_num == SIGTSTP && g_sig != 2)
	{
		sig_stp();
		return ;
	}
	if (g_sig == 2)
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
}
