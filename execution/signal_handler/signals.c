#include "../../inc/minishell.h"

void	sig_handler(int sig_num)
{
	char	*new_line;

	new_line = NULL;
	if (sig_num == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
	}
	else if (sig_num == SIGQUIT)
	{
		rl_on_new_line();
        rl_redisplay();
	}
}

void   here_doc_handler(int sig_num)
{

    if (sig_num == SIGINT)
    {
        write(STDOUT_FILENO, "\n", 1);
        g_exit_status = 130;
    }
    else if (sig_num == SIGQUIT)
        g_exit_status = 131;
}

void    setup_herdoc_signals(t_env **env, int fd)
{
    signal(SIGINT, here_doc_handler);
    signal(SIGQUIT, here_doc_handler);
    add_exit_status(env, g_exit_status);
    close(fd);
    exit(g_exit_status);
}

void setup_signals(void)
{
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN); 
}