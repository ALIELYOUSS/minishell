#include "minishell.h"

int main(int ac, char **av, char **env)
{
    char *prompt = "";
    (void)ac;
    (void)av;
    while (ft_strncmp(prompt, "exit", 4))
    {
        prompt = readline("$minishell >>: ");
        if (!ft_strncmp(prompt, "pwd", 3))
            ft_pwd();
        else if (!ft_strncmp(prompt, "env", 3))
            ft_env(env);
    }
}