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
// 
void    free_td(char **str)
{
    int i;

    i = -1;
    while (str[++i])
        free(str[i]);
}

void    handle_echo(char *prompt)
{
    char    **splited;

    if (ft_strncmp(prompt, "echo", ft_strlen(prompt)) == 0)
        return ;
    splited = ft_split(prompt, ' ');
    if (!splited)
        return ;
    ft_echo(splited);
    free_td(splited);
}

void    handle_builtin(char *prompt, t_env *env)
{
    if (!ft_strncmp(prompt, "exit", 4))
        ft_exit(env);
    else if (!ft_strncmp(prompt, "pwd", 3))
        ft_pwd();
    else if (!ft_strncmp(prompt, "env", 3))
        ft_env(env);
    else if (!ft_strncmp(prompt, "echo", 4))
        handle_echo(prompt);
    else if (!ft_strncmp(prompt, "cd", 2))
        ft_cd(prompt, env);
}

int is_builtin(char *prompt)
{
    if (!ft_strncmp(prompt, "echo", 4))
        return (1);
    else if (!ft_strncmp(prompt, "cd", 2))
        return (1);
    else if (!ft_strncmp(prompt, "env", 3))
        return (1);
    else if (!ft_strncmp(prompt, "exit", 4))
        return (1);
    else if (!ft_strncmp(prompt, "export", 6))
        return (1);
    else if (!ft_strncmp(prompt, "pwd", 3))
        return (1);
    else if (!ft_strncmp(prompt, "unset", 5))
        return (1);
    return (0);
}

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    t_env *env;
    char *prompt;
    pid_t pid;

    env = fill_env_list(envp);
    while (true)
    {
        prompt = readline("$minishell >>: ");
        if (is_builtin(prompt))
            handle_builtin(prompt, env);
        else
        {
            pid = fork();
            if (pid == 0)
                exec(prompt, env);
            else if (pid == -1)
                return (-1);
            else
                wait(NULL);
        }
    }
    return (0);
}
