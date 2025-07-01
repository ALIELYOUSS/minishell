/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 03:04:08 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/01 04:24:29 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int ft_unset(t_env **env, char *unseted)
{
    t_env   *tmp;
    t_env   *prev;
    t_env   *tmp_1;

    tmp = *env;
    tmp_1 = *env;
    prev = NULL;
    if (!*env)
        return (1);
    if (tmp && tmp->key && !ft_strncmp(tmp->key, unseted, ft_strlen(tmp->key)))
    {
        *env = tmp->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
        return (0);
    }
    while (tmp)
    {
        if (tmp->next && tmp->next->key && !ft_strncmp(tmp->next->key, unseted, ft_strlen(tmp->next->key)))
        {
            tmp_1 = tmp->next;
            tmp->next = tmp_1->next;
            free(tmp_1->key);
            free(tmp_1->value);
            free(tmp_1);
            return (0);
        }
        tmp = tmp->next;
    }
    puts("tzz");
    return (0);
}

int handle_unset(char *prompt, t_env **env)
{
    char **splited;

    splited = ft_split(prompt, ' ');
    if (!splited)
        return (1);
    else if (td_len(splited) > 2)
        return (0);
    if (splited[1])
        return (ft_unset(env, splited[1]));
    return (0);
}
