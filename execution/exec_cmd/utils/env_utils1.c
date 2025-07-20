/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:41:32 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/18 03:24:14 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*env_path(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	if (!tmp || !key)
	{
		perror("Error can not find path in env");
		return (NULL);
	}
	while (tmp)
	{
		if (tmp->key && ft_strcmp(tmp->key, key) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

char	**handle_empty_env(void)
{
	char	**env;
	char	*leaks;

	leaks = getcwd(NULL, 0);
	env = ft_malloc(sizeof(char *) * 5, sizeof(char *) * 5);
	if (!env)
		return (free(leaks), NULL);
	env[0] = ft_strjoin("PWD=", leaks);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("PATH=/.local/bin:/.local/bin:/.local/bin:");
	env[2] = simple_join(env[2], "/.local/bin:/usr/local/sbin:/usr/local/bin:");
	env[2] = simple_join(env[2], "/usr/sbin:/usr/bin:/sbin:/bin");
	env[3] = ft_strdup("_=/usr/bin/env");
	env[4] = NULL;
	free(leaks);
	return (env);
}

void	print_envp(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		else
			printf("%s\n", tmp->key);
		tmp = tmp->next;
	}
}
