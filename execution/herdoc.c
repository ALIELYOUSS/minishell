/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:04:42 by alel-you          #+#    #+#             */
/*   Updated: 2025/06/26 16:28:38 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int    herdoc_handler(char *delimiter)
{
    char    *input;
    int     line_len;
    int     fd[2];
    
    input = NULL;
    line_len = 0;
    if (pipe(fd) == -1)
    error_msg("pipe");
    while (1)
    {
        input = readline("> ");
        if (!input)
        break ;
        line_len = ft_strlen(input);
        if (!ft_strcmp(input, delimiter))
        {
            free(input);
            break ;
        }
        // printf("imput ============ %s\n", input);
        write(fd[1], input, line_len);
        write(fd[1], "\n", 1);
        free(input);
    }
    close(fd[1]);
    return (fd[0]);
}

void    exec_heredoc_cmd(t_cmd *cmd_list, char **env)
{
    int     read_fd;
    int     child;
    int     wait_child;
    t_cmd   *tmp;
    char    *delimiter;
    char    **cmd;

    cmd = ft_split(cmd_list->cmd, ' ');
    delimiter = find_delimiter(cmd_list, HRDOC);
    if (!delimiter || !cmd)
        error_msg("error");
    tmp = cmd_list;
    read_fd = herdoc_handler(delimiter);
    child = fork();
    if (!child)
    {
        if (dup2(read_fd, 0) == -1)
            error_msg("dup2");
        if (cmd[0] && !is_builtin(cmd[0]))
            exec(cmd[0], cmd_list->env_list, env);
        else if (cmd[0])
            handle_builtin(cmd[0], cmd_list->env_list);
        exit(EXIT_FAILURE);
    }
    else if (child == -1)
        error_msg("fork");
    close(read_fd);
    waitpid(child, &wait_child, 0);
}

void    exec_heredoc_cmd_pipe(t_cmd *cmd_list, char **env, int read_fd)
{
    char    *delimiter;

    delimiter = find_delimiter(cmd_list, HRDOC);
    if (!delimiter)
        error_msg("split failed");
    read_fd = herdoc_handler(delimiter);
    if (dup2(read_fd, 0) == -1)
        error_msg("dup2");
    if (!is_builtin(cmd_list->cmd))
        exec(cmd_list->cmd, cmd_list->env_list, env);
    else
        handle_builtin(cmd_list->cmd, cmd_list->env_list);
    exit(EXIT_FAILURE);
}

char    *get_heredoc_cmd(t_cmd *cmd_list)
{
    t_cmd   *tmp;
    char    *new_cmd;
    char    *delimiter;

    tmp = cmd_list;
    new_cmd = NULL;
    delimiter = find_delimiter(cmd_list, HRDOC);
    if (!delimiter)
        return (NULL);
    while (tmp)
    {
        if (tmp->cmd)
        {
            if (tmp->next->type == HRDOC)
            {
                new_cmd = join_it(tmp->cmd, " ");
                new_cmd = join_it(new_cmd, "<<");
                new_cmd = join_it(new_cmd, " ");
                new_cmd = join_it(new_cmd, delimiter);
                free(delimiter);
                return (new_cmd);
            }
        }
        tmp = tmp->next;
    }
    return (new_cmd);
}

void    set_hrdoc_fd(t_cmd **cmd)
{
    t_cmd   *tmp;
    char    **new_cmd;

    tmp = cmd;
    new_cmd = NULL;
    while (tmp)
    {
        if (tmp->redir && tmp->redir->type == HRDOC)
        {
            new_cmd = ft_split(tmp->cmd, ' ');
            tmp->cmd = new_cmd[0];
            tmp->redir->fd = herdoc_handler(tmp->redir->file);
            free_td(new_cmd);
        }
        tmp = tmp->next;
    }
}
