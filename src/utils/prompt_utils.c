/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:43:54 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/09 19:28:17 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_break(char *prompt)
{
	int	i;

	if (!prompt)
		return (0);
	i = 0;
	while (ft_isspace(prompt[i]))
		i++;
	if (prompt[i] && !ft_strncmp("exit", &prompt[i], 4))
	{
		i += 4;
		while (ft_isspace(prompt[i]))
			i++;
		if (!prompt[i])
			return (0);
	}
	return (1);
}

int	finish_prompt(char *prompt)
{
	if (!ft_break(prompt))
	{
		if (prompt)
			free(prompt);
		return (0);
	}
	return (1);
}

void	handle_export_value_cases(t_env **e_tmp, char *value, int *f)
{
	if ((*e_tmp) && (!(*e_tmp)->value || *f == 1))
	{
		(*e_tmp)->value = simple_join((*e_tmp)->value, value);
		(*e_tmp)->f = 1;
	}
	else if ((*e_tmp) && (!(*e_tmp)->value || f == 0))
	{
		(*e_tmp)->value = value;
		(*e_tmp)->f = 1;
	}
}

int	check_identifier(char *key)
{
	if (!key)
	{
		write(2, "Memory Error\n", 13);
		return (0);
	}
	if (!valid_identifier(key))
	{
		printf("bash: export: `%s': not a valid identifier\n", key);
		return (0);
	}
	return (1);
}
