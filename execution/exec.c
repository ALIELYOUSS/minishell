#include "../minishell.h"

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

void    exec(char *prompt, t_env *env)
{
    int i;
    char *path;
    char **paths;
    char *cmd_path;
    char **tokens;

    i = 0;
    tokens = ft_split(prompt, ' ');
    if (!tokens)
        return ;
    path = NULL;
    path = env_path(env, "PATH");
    paths = ft_split(path, ':');
    if (!paths)
        return ;
    while (paths[i])
    {
        cmd_path = add_cmd_to_path(paths[i], tokens[0]);
        if (!access(cmd_path, X_OK))
        {
            execve(cmd_path, tokens, NULL);
            free(cmd_path);
        }
        i++;
    }
    i = 0;
    while (paths[i++])  
        free(paths[i]);
    free(paths);
}