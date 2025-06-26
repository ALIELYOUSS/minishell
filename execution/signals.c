#include "../inc/minishell.h"
#include <signal.h>

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

void    setup_child_signals(int flag)
{
    int pid;

    pid = fork();
    if (flag == 1 && !pid)
        signal(SIGINT, SIG_DFL);
    else
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
    }
}
void setup_signals(void)
{
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN); 
}