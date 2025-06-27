/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:04:42 by alel-you          #+#    #+#             */
/*   Updated: 2025/06/27 16:45:59 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
        write(fd[1], input, line_len);
        write(fd[1], "\n", 1);
        free(input);
    }
    close(fd[1]);
    return (fd[0]);
}

void    exec_heredoc_cmd(t_cmd *cmd_list, char **env, t_env *env_list)
{
    int     child;
    int     wait_child;
    t_cmd   *tmp;
    char    *delimiter;

    delimiter = find_delimiter(cmd_list, HRDOC);
    if (!delimiter)
        error_msg("error");
    set_hrdoc_fd(cmd_list, NULL);
    tmp = cmd_list;
    child = fork();
    if (tmp->redir && tmp->redir->type == HRDOC)
    {
        if (!child)
        {
            if (dup2(tmp->redir->fd, 0) == -1)
                error_msg("dup2");
            if (tmp->cmd && !is_builtin(tmp->cmd))
                exec(tmp->cmd, env_list, env);
            else if (tmp->cmd)
                handle_builtin(tmp->cmd, env_list);
            exit(EXIT_FAILURE);
        }
        close(tmp->redir->fd);
    }
    else if (child == -1)
        error_msg("fork");
    waitpid(child, &wait_child, 0);
}

void    set_hrdoc_fd(t_cmd *cmd, t_list *tokens)
{
    t_cmd   *tmp;
    t_tokens    *tmp_t;

    if (cmd)
    {
        tmp = cmd;
        while (tmp)
        {
            if (tmp->redir && tmp->redir->type == HRDOC)
                tmp->redir->fd = herdoc_handler(tmp->redir->file);
            tmp = tmp->next;
        }
    }
    if (tokens)
    {
        int tmp_fd;
        
        tmp_t = tokens->head;
        tmp_fd = herdoc_handler(tmp_t->next->content);
        close(tmp_fd);
    }
}
