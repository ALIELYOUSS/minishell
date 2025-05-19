#include "minishell.h"

void    error_msg(char *str)
{
    printf("%s\n", str);
    exit(EXIT_FAILURE);
}

int td_len(char **str)
{
    int i;

    i = 1;
    while (str[i])
        i++;
    return (i);
}