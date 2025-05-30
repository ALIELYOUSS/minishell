#include "pipex.h"
// uncomplited pipex
void    open_files(char *input, char *output, int *in_fd, int *out_fd)
{
    *in_fd = 0;
    *out_fd = 0;
    *in_fd = open(input, O_RDONLY | O_CREAT, 0777);
    *out_fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (*out_fd == -1)
        error_msg("bad file_d out");
    if (*in_fd == -1)
        error_msg("bad file_d in");
}

void pipex(int in_fd, char *cmd1, char *cmd2, int out_fd, t_env *env)
{
    int ends[2];
    int child_1;
    int child_2;

    if (pipe(ends) == -1)
        error_msg("pipe");
        
    child_1 = fork();
    if (child_1 == -1)
        error_msg("fork");
    if (child_1 == 0)
    {
        if (dup2(in_fd, 0) == -1 || dup2(ends[1], 1) == -1)
            error_msg("dup2");
        close(ends[0]);
        close(ends[1]);
        close(in_fd);
        close(out_fd);
        exec(cmd1, env);
        exit(EXIT_FAILURE);
    }
    
    child_2 = fork();
    if (child_2 == -1)
        error_msg("fork");
    if (child_2 == 0)
    {
        if (dup2(ends[0], 0) == -1 || dup2(out_fd, 1) == -1)
            error_msg("dup2");
        close(ends[0]);
        close(ends[1]);
        close(in_fd);
        close(out_fd);
        exec(cmd2, env);
        exit(EXIT_FAILURE);
    }
    close(ends[0]);
    close(ends[1]);
    waitpid(child_1, NULL, 0);
    waitpid(child_2, NULL, 0);
}

int main(int ac, char **av, char **envp)
{
    int in_fd;
    int out_fd;
    t_env *env;

    (void)av;
    (void)envp;
    env = fill_env_list(envp);
    if (!env)
        return (-1);
    if (ac == 5)
    {
        open_files(av[1], av[4], &in_fd, &out_fd);
        pipex(in_fd, av[2], av[3], out_fd, env);
    }
    else
    {
        ft_putstr_fd("Incorrect number of arguments.\n", 2);
        return (-1);
    }
}