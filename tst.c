// char	*append_cmd_to_path(char *path, char *cmd)
// {
// 	char	*path_slash;
// 	char	*ret;

// 	path_slash = ft_strjoin(path, "/");
// 	if (!path)
// 		return (NULL);
// 	ret = ft_strjoin(path_slash, cmd);
// 	if (!ret)
// 		return (NULL);
// 	free(path_slash);
// 	return (ret);
// }

// void  exec(t_env *env, char *prompt)
// {
// 	char	**args;
// 	t_env	*current;
//     char	*path_var;
// 	char	*cmd_path;
// 	char	**paths;
//     int		i;
    
// 	args = ft_split(prompt, ' ');
// 	if (!args)
// 		return ;
// 	current = env;
// 	while (current)
// 	{
// 		if (!ft_strncmp(current->key, "PATH", 4))
// 		{
// 			path_var = ft_strdup(current->value);
// 			if (!path_var)
// 				return ;
// 		}
// 		current = current->next;
// 	}
// 	paths = ft_split(path_var, ':');
// 	if (!paths)
// 		return ;
// 	free(path_var);
// 	i = 0;
// 	while (paths[i])
// 	{
// 		cmd_path = append_cmd_to_path(paths[i], args[0]);
// 		if (!cmd_path)
// 			return ;
// 		if (!access(cmd_path, X_OK))
// 		{
// 			execve(cmd_path, args , NULL);
// 			free(cmd_path);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (paths[i++])
// 		free(paths[i]);
// 	free(paths);
// }
