/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:55:36 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/05 23:38:15 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*add_cmd_to_path(char *path, char *cmd)
{
	char	*path_slash;
	char	*ret;
	char	*tmp;

	tmp = NULL;
	path_slash = ft_strjoin(path, "/");
	if (!path_slash)
		return (NULL);
	ret = ft_strjoin(path_slash, cmd);
	if (!ret)
		return (free(path_slash), NULL);
	free(path_slash);
	return (ret);
}

void	exec_fail_case(int status)
{
	if (status != 0)
		exit(EXIT_FAILURE);
}

void	exec(char *prompt, t_env *env, char **env_p)
{
	char	*cmd_path;
	char	**tokens;

	cmd_path = NULL;
	tokens = ft_split(prompt, ' ');
	if (!tokens)
		error_msg("split");
	cmd_path = return_path(tokens[0], env);
	if (!cmd_path)
	{
		if (ft_strchr(tokens[0], '/'))
			exec_fail_case(execve(tokens[0], tokens, env_p));
	}
	else
		exec_fail_case(execve(cmd_path, tokens, env_p));
	free(cmd_path);
}

void	free_td(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	handle_builtin(char *prompt, t_env **env)
{
	if (!ft_strncmp(prompt, "exit", 4))
		return (ft_exit(prompt, *env));
	else if (!ft_strncmp(prompt, "pwd", 3))
		return (ft_pwd());
	else if (!ft_strncmp(prompt, "env", 3))
		return (ft_env(*env));
	else if (!ft_strncmp(prompt, "echo", 4))
		return (handle_echo(prompt));
	else if (!ft_strncmp(prompt, "cd", 2))
		return (ft_cd(prompt, env));
	else if (!ft_strncmp(prompt, "export", 6))
		return (ft_export(prompt, *env));
	else if (!ft_strncmp(prompt, "unset", 5))
		return (handle_unset(prompt, env));
	return (-1337);
}

char	**fake_env()
{getcwd(NULL, 0);
	char** env = malloc(sizeof(char *)*5);
	if (!env)
	return(printf("error\n"),NULL);
	env[0]= join_it("PWD=",getcwd(NULL, 0));
	env[1] = ft_strdup("SHLVL=1");
	env[2]= ft_strdup("PATH=/.local/bin:/.local/bin:/.local/bin:/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	env[3] = ft_strdup("_=usr/cin/env");
	env[4]= NULL;
	return (env);
	
}

