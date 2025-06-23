/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:04:42 by alel-you          #+#    #+#             */
/*   Updated: 2025/06/23 19:29:45 by alel-you         ###   ########.fr       */
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
    t_cmd   *tmp;
    int     wait_child;

    tmp = cmd_list;
    read_fd = herdoc_handler(tmp->next->next->cmd);
    child = fork();
    if (!child)
    {
        if (dup2(read_fd, 0) == -1)
            error_msg("dup2");
        else if (!is_builtin(cmd_list->cmd))
            exec(cmd_list->cmd, cmd_list->env_list, env);
        else
            handle_builtin(cmd_list->cmd, cmd_list->env_list);
        exit(EXIT_FAILURE);
    }
    else if (child == -1)
        error_msg("fork");
    close(read_fd);
    waitpid(child, &wait_child, 0);
}

void    exec_heredoc_cmd_pipe(t_cmd *cmd_list, char **env, int read_fd)
{
    read_fd = herdoc_handler(cmd_list->next->next->cmd);
    if (dup2(read_fd, 0) == -1)
        error_msg("dup2");
    else if (!is_builtin(cmd_list->cmd))
        exec(cmd_list->cmd, cmd_list->env_list, env);
    else
        handle_builtin(cmd_list->cmd, cmd_list->env_list);
    exit(EXIT_FAILURE);
}