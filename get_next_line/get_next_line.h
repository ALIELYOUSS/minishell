/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:38:13 by alel-you          #+#    #+#             */
/*   Updated: 2025/06/17 23:30:26 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include "../inc/minishell.h"
# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 13
# endif

char	*ft_getline(char *rest);
char	*get_next_line(int fd);
char	*ft_get_rest(char *str);

#endif
