#include "../inc/minishell.h"

int     is_heredoc(t_cmd *cmd_list)
{
    t_cmd   *tmp;

    tmp = cmd_list;
    while (tmp)
    {
        if (tmp->type == HRDOC)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

int delimiter_len(t_cmd *cmd_list, t_type to_find)
{
    t_cmd   *tmp;


    tmp = cmd_list;
    while (tmp)
    {
        if (tmp->type == to_find)
            return (ft_strlen(tmp->next->cmd));
        tmp = tmp->next;
    }
    return (0);
}

char    *find_delimiter(t_cmd *cmd_list, t_type to_find)
{
    t_cmd   *tmp;

    tmp = cmd_list;
    while (tmp)
    {
        if (tmp->type == to_find)
            return (ft_strdup(tmp->next->cmd));
        tmp = tmp->next;
    }
    return (NULL);
}

// t_cmd   *list_cutter(t_cmd *list, t_type cut_killer)
// {
//     t_cmd   *tmp;
//     t_cmd   *ret;

//     tmp = list;
//     ret = malloc(sizeof(list));
//     if (!ret)
//         return (NULL);
//     while (tmp)
//     {
//         if (ret->cmd)
//             printf("%s\n", ret->cmd);
//         printf("%d\n", ret->type);
//         if (tmp->type == cut_killer)
//             ret->next->next = NULL;
//         if (!ret->next)
//             return (ret);
//         tmp = ret;
//         ret = ret->next;
//         tmp = tmp->next;
//     }
//     return (NULL);
// }
void	print_cmd(t_cmd *cmd)
{
	t_cmd *tmp;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->cmd)
			printf("%s\n", tmp->cmd);
		else 
			printf("%d\n", tmp->type);
		tmp = tmp->next;
	}
}

int size_of_it(t_cmd *cmd)
{
    t_cmd   *tmp;
    int     size;

    tmp = cmd;
    size = 0;
    while (tmp)
    {
        if (tmp->type == HRDOC && tmp->next->cmd)
        {
            size += ft_strlen(tmp->cmd);
            tmp = tmp->next;
            size += ft_strlen(tmp->cmd);
            return (size);
        }
        if (tmp->cmd)
            size += ft_strlen(tmp->cmd);
        tmp = tmp->next;
    }
    return (0);
}

char    *parse_heredoc(t_cmd *cmd_list)
{
    t_cmd   *tmp;
    char    *new_cmd;

    tmp = cmd_list;
    new_cmd = malloc(size_of_it(cmd_list) + 1);
    if (!new_cmd)
        return (NULL);
    while (tmp)
    {
        if (tmp->cmd)
        {
            if (tmp->type == HRDOC)
                new_cmd = join_it(new_cmd, "<<");
            new_cmd = join_it(new_cmd, tmp->cmd);
        }
        if (!tmp->cmd && tmp->type != HRDOC)
            break ;
        tmp = tmp->next;
    }
    return (new_cmd);
}

void handle_pipe(t_cmd *cmd_list, t_env *env_list, char **env)
{
    t_cmd   *tmp;
    int     *pipe_fds;
    pid_t   *children;
    int     num_cmds;
    int     i;
    int     j;
    int     flag;
    
    i = 0;
    j = -1;
    flag = -1;
    tmp = cmd_list;
    num_cmds = pipe_counter(cmd_list) + 1;
    children = malloc(sizeof(pid_t) * num_cmds);
    pipe_fds = malloc(sizeof(int) * (2 * (num_cmds)));
    if (!children || !pipe_fds)
        error_msg("malloc");
    while (++j < num_cmds - 1)
    {
        if (pipe(pipe_fds + j * 2) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }
    while (tmp)
    {
        if (tmp->type == HRDOC)
            flag = 1;
        if (tmp->cmd == NULL)
        {
            tmp = tmp->next;
            continue ;
        }
        children[i] = fork();
        if (children[i] < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (children[i] == 0)
        {
            if (i > 0)
                dup2(pipe_fds[(i - 1) * 2], 0);
            else if (tmp->next)
                dup2(pipe_fds[i * 2 + 1], 1);
            else if (flag == 1)
            {
                int hrdoc = herdoc_handler(find_delimiter(cmd_list, HRDOC));
                dup2(hrdoc, 0);
            }
            j = -1;
            while (++j < 2 * (num_cmds - 1))
                close(pipe_fds[j]);
            if (!is_builtin(tmp->cmd))
                exec(tmp->cmd, env_list, env);
            else
                handle_builtin(tmp->cmd, env_list);
            
            exit(EXIT_FAILURE);
        }
        tmp = tmp->next;
        i++;
    }
    j = -1;
    while (++j < 2 * (num_cmds - 1))
        close(pipe_fds[j]);
    j = -1;
    while (++j < num_cmds)
        waitpid(children[j], NULL, 0);
}

int    execution(t_cmd *cmd_list, char **env)
{
    t_cmd   *tmp;
    t_env   *env_list; 
    pid_t    i;
    int      ps;
    int      hrdoc_fd;
    
    hrdoc_fd = 0;
    tmp = cmd_list;
    env_list = fill_env_list(env);
    if (!env_list)
        return (-1);
    i = fork();
    if (!i)
    {
        if (tmp && tmp->type == CMD && pipe_counter(cmd_list) > 0)
        {
            handle_pipe(cmd_list, env_list, env);
            exit(EXIT_SUCCESS);
        }
        if (tmp && tmp->type == CMD && tmp->cmd && is_builtin(tmp->cmd))
            handle_builtin(tmp->cmd, env_list);
        while (tmp)
        {
            if (tmp->type == OUT || tmp->type ==IN || tmp->type == APP)
                handel_redect(tmp);
            else if (!is_builtin(tmp->cmd))
                exec(tmp->cmd, env_list, env);
            tmp = tmp->next;
        }
        exit(EXIT_SUCCESS);
    }
    waitpid(i, &ps, 0);
    return (0);
}