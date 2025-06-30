/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 03:29:19 by yael-maa          #+#    #+#             */
/*   Updated: 2025/06/30 05:56:30 by yael-maa         ###   ########.fr       */
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
		if (tmp->value)
			printf("%s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("%s\n", tmp->key);
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

int	valid_identifier(char *cmd, t_env *env)
{
	t_env	*tmp;
	int		i;
	int		f;

	i = 0;
	f = 0;
	if ((cmd[i] < 'a' || cmd[i] > 'z') && (cmd[i] < 'A' || cmd[i] > 'Z') && cmd[i] != '_')
		return(0);
	while (cmd[++i] && cmd[i] != '=')
	{
		if (cmd[i] == '+' && cmd[i + 1] && cmd[i + 1] == '=')
		{
			f = -1;
			break ;	
		}
		else if ((cmd[i] < 'a' || cmd[i] > 'z') && (cmd[i] < 'A' || cmd[i] > 'Z') && cmd[i] != '_' && (cmd[i] < '0' || cmd[i] > '9'))
			return(0);
	}
	tmp = env;
	while (tmp)
	{
		if (!strncmp(cmd, tmp->key, ft_strlen(tmp->key)) && f == -1)
			return (2);
		else if (!strncmp(cmd, tmp->key, ft_strlen(tmp->key)))
			return (-1);
		tmp = tmp->next;
	}
	if (f == -1)
		return (3);
	return (1);	
}

char	*retrieve(char *arg)
{
	char	*retrieved;
	int		i;
	int		j;

	retrieved = malloc(ft_strlen(arg));
	if (!retrieved)
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i] && arg[i] != '+')
	{
		retrieved[j] = arg[i];
		j++;
		i++;
	}
	while(arg[++i])
	{
		retrieved[j] = arg[i];
		j++;
	}
	retrieved[j] = '\0';
	return (retrieved);
}

void	ft_export(char *cmd, t_env *env)
{
	t_env	*node;
	t_env	*tmp;
	char	*arg;
	char	*clean;
	int		f;
	int		i;

	node = NULL;
	f = 0;
	// clean = ft_strchr(cmd , '=');
	if (ft_strlen(cmd) == 6 && !ft_strncmp(cmd, "export", 6))
	{
		tmp = sort_env_lst(env);// print 'a' in export but not in env if there's no '='  and empty string if there's just '='
		print_env(tmp, "declare -x ");
	}
	else
	{
		arg = get_arg(cmd, 6);
		// printf("===========%s\n", arg);
		if (!arg)
		{
			write(2, "Memory Error\n", 13);
			return ;
		}
		f = valid_identifier(arg, env);
		// printf("==========%d\n", f);
		if (f == 1)
		{
			node = create_env_node(arg);
			if (!node)
				return ;
			tmp = env;
			while(tmp->next)
				tmp = tmp->next;
			tmp->next = node;
			node->next = NULL;
			return ;
		}
		else if (f == 2)
		{
			i = 0;
			while (cmd[i] && cmd[i] != '=')
				i++;
			i++;
			tmp = env;
			while (tmp)
			{
				if (!ft_strncmp(tmp->key, arg, ft_strlen(tmp->key)))
				{
					tmp->value = simple_join(tmp->value, &cmd[i]);
					return ;
				}
				tmp = tmp->next;
			}
		}
		else if (f == 3)
		{
			clean = retrieve(arg);
			node = create_env_node(clean);
			if (!node)
				return ;
			tmp = env;
			while(tmp->next)
				tmp = tmp->next;
			tmp->next = node;
			node->next = NULL;
			// printf("===========%s\n", clean);
			return ;
		}
		else if (!f)
		{
			printf("export: '%s': not a valid identifier\n", arg);
			return ;
		}
	}
}