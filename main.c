#include "minishell.h"

// void    print(t_env *enp)
// {
//     t_env *current;

//     current = enp;
//     while (current)
//     {
//        if (current->value)
//             printf("%s=%s\n", current->key, current->value);
//         else
//             printf("%s\n", current->key);
//         current = current->next;
//     }
//     exit(0);
// }

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    t_env *env;
    char *prompt = "";

    env = fill_env_list(envp);
    (void)env;
    while (ft_strncmp(prompt, "exit", 4))
    {
        prompt = readline("$minishell >>: ");
        if (!ft_strncmp(prompt, "pwd", 3))
            ft_pwd();
        else if (!ft_strncmp(prompt, "env", 3))
            ft_env(env);
    }
}
