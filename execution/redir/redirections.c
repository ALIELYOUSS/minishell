/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 23:17:14 by alel-you          #+#    #+#             */
/*   Updated: 2025/06/27 23:51:19 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void    handl_out_redir(int fd, char **env, t_env *env_list)
// {
//     t_cmd   *cmd;
//     int     pid;
//     int     ps;

//     ps = 0;
//     pid = fork();
//     if (!pid)
//     {
//         if (dup2(fd, 0) == -1)
//             error_msg("dup2");
//         if (!is_builtin(cmd->cmd))
//             exec(cmd->cmd, env_list, env);
//         else
//             handle_builtin(cmd->cmd, env_list);
//         exit(EXIT_FAILURE);
//     }
//     waitpid(pid, &ps, NULL);
// }

