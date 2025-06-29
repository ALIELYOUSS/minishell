/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 03:29:19 by yael-maa          #+#    #+#             */
/*   Updated: 2025/06/29 18:07:48 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*sort_env_lst(t_env *env)
{
	t_env	*sorted_env;
	t_env	*tmp;
	t_env	*tmp_next;
	t_env	*swap;
	int		i;
    int     x;

	tmp = env;
    x = -1;
	while (tmp)
	{
		i = 0;
		tmp_next = tmp->next;
		while (tmp_next)
		{
			while (tmp->key[i] && tmp_next->key[i] && tmp->key[i] <= tmp_next->key[i])
			{
				if (tmp->key[i] > tmp_next->key[i])
				{
					swap = tmp;
					tmp = tmp_next;
					tmp_next = swap;
					break ;
				}
				i++;
			}
			tmp_next = tmp_next->next;
		}
        if (x == -1)
		{
            sorted_env = tmp;
			x = 0;
		}
		tmp = tmp->next;
	}
	return (sorted_env);
}

void	print_env(t_env *env, char *s)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (s)
			printf("%s", s);
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

char	*get_arg(char *cmd, int index)
{
	char	*arg;
	int		i;
	int		j;

	while (cmd[index] && ft_isspace(cmd[index]))
		index++;
	i = index;
	while (cmd[index] && !ft_isspace(cmd[index]))
		index++;
	arg = malloc(index - i + 1);
	if (!arg)
		return (NULL);
	j = 0;
	while (cmd[i])
	{
		arg[j] = cmd[i];
		i++;
		j++;
	}
	arg[j] = '\0';
	return (arg);
}

int	valid_identifier(char *cmd)
{
	int	i;

	i = 0;
	if ((cmd[i] < 'a' || cmd[i] > 'z') && (cmd[i] < 'A' || cmd[i] > 'Z') && cmd[i] != '_')
		return(0);
	while (cmd[++i] && cmd[i] != '=')
	{
		if ((cmd[i] < 'a' || cmd[i] > 'z') && (cmd[i] < 'A' || cmd[i] > 'Z') && cmd[i] != '_' && (cmd[i] < '0' || cmd[i] > '9'))
			return(0);
	}
	return (1);	
}

void	ft_export(char *cmd, t_env *env)
{
	t_env	*node;
	t_env	*tmp;
	char	*arg;

	node = NULL;
	if (ft_strlen(cmd) == 6 && !ft_strncmp(cmd, "export", 6))
	{
		tmp = sort_env_lst(env);
		print_env(tmp, "declare -x ");
	}
	else
	{
		arg = get_arg(cmd, 6);
		if (valid_identifier(arg))
		{
			node = create_env_node(arg);
			if (!node)
				return ;
			tmp = env;
			while(tmp->next)
				tmp = tmp->next;
			tmp->next = node;
		}
		else
		{
			printf("export: '%s': not a valid identifier\n", arg);
			return ;
		}
	}
}