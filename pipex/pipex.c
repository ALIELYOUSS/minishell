#include "pipex.h"
// uncomplited pipex
void    open_files(char *input, char *output, int *in_fd, int *out_fd)
{
    *in_fd = open(input, O_RDONLY);
    if (*in_fd == -1)
    {
        perror("open");
        return ;
    }
    *out_fd = open(output, O_WRONLY | O_CREAT);
    if (*out_fd == -1)
    {
        perror("open");
        return ;
    }
}

char    *add_cmd_to_path(char *path, char *cmd)
{
    char *path_slash;
    char *ret;

    path_slash = ft_strjoin(path, "/");
    if (!path_slash)
        return (NULL);
    ret = ft_strjoin(path_slash, cmd);
    if (!ret)
        return (NULL);
    free(path_slash);
    return (ret);
}

char *env_path(char **env, char *key)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0)
			return (ft_strdup(env[i]));
		i++;
	}
	return (NULL);
}

void    exec_path(char **env, char *command)
{
    char    **cmd_split;
    char    *cmd_path;
    char    **env_split;
    char    *path;
    int     i;

    path = env_path(env, "PATH");
    env_split = ft_split(path + 5, ':');
    cmd_split = ft_split(command, ' ');
    cmd_path = NULL;
    i = 0;
    while (env_split[i])
    {
        cmd_path = add_cmd_to_path(env_split[i], command);
        if (!access(cmd_path, X_OK))
        {
            if (execve(cmd_path, cmd_split, env) == -1)
            {
                perror("execve");
                return ;
            }
        }
        i++;
    }
}

void    pipex(int in_fd, char *cmd1, char *cmd2, int out_fd, char **env)
{
    int ends[2];
    int pid1;
    int pid2;

    if (!pipe(ends))
    {
        pid1 = fork();
        if (!pid1)
        {
            if (dup2(0, in_fd) > 0 || dup2(1, ends[1]) > 0)
                exec_path(env, cmd1);
            else
            {
                perror("dup2");
                return ;
            }
        }
        pid2 = fork();
        if (!pid2)
        {
            if (dup2(0, ends[0]) > 0 || dup2(1, out_fd) > 0)
            {
                exec_path(env, cmd2);
                puts("here");
            }
            else
            {
                perror("dup2");
                return ;
            }
        }
    }
    else
    {
        perror("pipe");
        return ;
    }
}

int main(int ac, char **av, char **envp)
{
    int in_fd;
    int out_fd;

    (void)av;
    (void)envp;
    if (ac == 5)
    {
        open_files(av[1], av[4], &in_fd, &out_fd);
        pipex(in_fd, av[2], av[3], out_fd, envp);
    }
    else
    {
        ft_putstr_fd("Incorrect number of arguments.\n", 2);
        return (-1);
    }
}