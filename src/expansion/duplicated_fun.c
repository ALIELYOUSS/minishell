/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicated_fun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:18:52 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/22 09:22:37 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*exit_expand_2(t_redir **tmp, int *i)
{
	char	*par_value;

	if ((*tmp)->file[*i] && (*tmp)->file[*i + 1] && (*tmp)->file[*i + 1] == '?')
		par_value = ft_itoa(get_exit_status(0, GET));
	else
		return (NULL);
	return (par_value);
}
