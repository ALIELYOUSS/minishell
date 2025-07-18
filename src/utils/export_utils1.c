/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 07:01:57 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/18 00:37:45 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	export_quoting(char **arg, int *i)
{
	int	f;

	f = valid_identifier2(arg[*i]);
	if (quotes_ps(arg[*i]))
		arg[*i] = replace_quotes(arg[*i]);
	if (!f)
	{
		printf("bash: export: `%s': not a valid identifier\n", arg[*i]);
		(*i)++;
		return (0);
	}
	return (1);
}

int	invalid_key_msg(char *key, int *i)
{
	if (!valid_identifier(key))
	{
		printf("minishell: export: `%s': not a valid identifier\n", key);
		(*i)++;
		return (0);
	}
	return (1);
}
