/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:44:57 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/16 23:15:30 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    write_echo_line(char *str, int fd)
{
    int i;

    i = 0;
    while (str && str[i])
        ft_putchar_fd(str[i++], fd);  
}

char	*point_arg(char *str, char *path)
{
	char	*new_path;
	int		len;

	new_path = NULL;
	if (!path)
		return (printf("path?\n"), NULL );
	len = ft_strlen(path);
	if ((!path[len - 1] != '/') && (path[len - 1] == '.' && path[len - 2] == '.'))
		new_path = join_it(path, "/");
	else if (!ft_strcmp(str, ".") && path[len] && path[len - 1] == '.' && path[len - 2] != '.')
		new_path = join_it(new_path, ".");
	else if (!ft_strcmp(str, "..") && path[len] && path[len - 1] == '.' && path[len - 2] == '.')
		new_path = join_it(new_path, "./.");
	return (new_path);
}
