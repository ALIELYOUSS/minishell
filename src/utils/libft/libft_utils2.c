/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 04:33:10 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/17 06:59:51 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	clear_list(t_list *tokens)
{
	t_tokens	*tmp;

	if (!tokens)
		return ;
	tmp = NULL;
	while (tokens->head)
	{
		tmp = tokens->head;
		tokens->head = tokens->head->next;
		if (tmp->content)
		{
			free(tmp->content);
			tmp->content = NULL;
		}
		free(tmp);
		tokens->size--;
		tmp = NULL;
	}
	tokens->head = NULL;
	tokens->tail = NULL;
}

void	rq_strcpy(char *cmd, char *final_cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(cmd))
	{
		if (cmd[i] == -1)
			i++;
		if (cmd[i] && cmd[i] != -1)
		{
			final_cmd[j] = cmd[i];
			j++;
			i++;
		}
	}
	free(cmd);
	final_cmd[j] = '\0';
}

void	print_env(t_env *env, char *s, int fd)
{
	t_env	*tmp;

	tmp = env;
	sort_env(&tmp);
	while (tmp)
	{
		if (s && tmp->key)
			ft_putstr_fd(s, fd);
		if (tmp->value || tmp->f == 1)
			print_it(tmp->key, tmp->value, fd);
		else if (!tmp->value && tmp->f == 1)
		{
			ft_putstr_fd(tmp->key, fd);
			ft_putchar_fd('\n', fd);
		}
		else if (tmp->key && tmp->f != 1)
		{
			ft_putstr_fd(tmp->key, fd);
			ft_putchar_fd('\n', fd);
		}
		if (tmp)
			tmp = tmp->next;
	}
}

void	ft_help_free(char *bef_var, char *par_name)
{
	if (par_name)
		free(par_name);
	if (bef_var)
		free(bef_var);
}

char	*exit_expand(t_cmd **tmp, int *i, char *par_name, char *bef_var)
{
	char	*par_value;

	if ((*tmp)->cmd[*i] && (*tmp)->cmd[*i + 1] && (*tmp)->cmd[*i + 1] == '?')
		par_value = *(leak_killer(ft_itoa(get_exit_status(0, GET)), SET));
	else
	{
		ft_help_free(par_name, bef_var);
		return (NULL);
	}
	return (par_value);
}
