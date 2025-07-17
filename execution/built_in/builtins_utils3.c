/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 22:49:08 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/17 22:52:08 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**leak_killer(char *str, int flag)
{
	static char	*to_free;

	if (flag == SET && str != NULL)
	{
		if (to_free != NULL)
			free(to_free);
		to_free = str;
	}
	else if (flag == FREE)
		free(to_free);
	return (&to_free);
}
