#include "minishell.h"

void    ft_exit()
{
    // printf("exit\n");
    ft_putstr_fd("exit\n", 1);
    exit(0);
}