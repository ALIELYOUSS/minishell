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

// char    *add_cmd_to_path(char *path, char *cmd)
// {
//     char *path_slash;
//     char *ret;

//     path_slash = ft_strjoin(path, "/");
//     if (!path_slash)
//         return (NULL);
//     ret = ft_strjoin(path_slash, cmd);
//     if (!ret)
//         return (NULL);
//     free(path_slash);
//     return (ret);
// }

// char *env_path(char **env, char *key)
// {
// 	int i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0)
// 			return (ft_strdup(env[i] + ft_strlen(key)));
// 		i++;
// 	}
// 	return (NULL);
// }

// void    exec_path(char **env, char *command)
// {
//     char    **cmd_split;
//     char    *cmd_path;
//     char    **env_split;
//     char    *path;
//     int     i;

//     path = env_path(env, "PATH=");
//     env_split = ft_split(path, ':');
//     cmd_split = ft_split(command, ' ');
//     cmd_path = NULL;
//     i = 0;
//     while (env_split[i])
//     {
//         cmd_path = add_cmd_to_path(env_split[i], cmd_split[0]);
//         if (!access(cmd_path, X_OK))
//         {
//             if (execve(cmd_path, cmd_split, env) == -1)
//             {
//                 perror("execve");
//                 return ;
//             }
//         }
//         i++;
//     }
// }

// void    pipex(int in_fd, char *cmd1, char *cmd2, int out_fd, t_env *env)
// {
//     int ends[2];
//     int pid1;
//     int pid2;

//     pid1 = 0;
//     pid2 = 0;
//     if (!pipe(ends))
//     {
//         pid1 = fork();
//         if (pid1 == 0)
//         {
//             if (dup2(in_fd, 0) == -1 || dup2(ends[1], 1) == -1)
//             {
//                 perror("dup2");
//                 exit(EXIT_FAILURE);
//             }
//             close(ends[0]);
//             close(ends[1]);
//             close(in_fd);
//             close(out_fd);  
//             exec(cmd1, env);
//             exit(EXIT_SUCCESS);
//         }
//         pid2 = fork();
//         if (pid2 == 0)
//         {
//             if (dup2(ends[0], 0) == -1 || dup2(out_fd, 1) == -1)
//             {
//                 perror("dup2");
//                 exit(EXIT_FAILURE);
//             }
//             close(ends[0]);
//             close(ends[1]);
//             close(in_fd);
//             close(out_fd);
//             exec(cmd2, env);
//             exit(EXIT_SUCCESS);
//         }
//     }
//     else
//     {
//         perror("pipe");
//         return ;
//     }
//     close(ends[0]);
//     close(ends[1]);
//     waitpid(pid1, NULL, 0);
//     waitpid(pid2, NULL, 0);
// }


// void    pipex(int in_fd, char *cmd1, char *cmd2, int out_fd, t_env *env)
// {
//     int ends[2];
//     int child_1;
//     int child_2;

//     if (pipe(ends) == -1)
//         error_msg("pipe");
//     child_1 = fork();
//     if (child_1 == 0)
//     {
//         if (dup2(in_fd, 0) == -1 || dup2(ends[1], 1) == -1)
//             error_msg("dup2");
//         close(ends[0]);
//         close(ends[1]);
//         close(in_fd);
//         close(out_fd);
//         exec(cmd1, env);
//         exit(EXIT_FAILURE);
//     }
//     else if (child_1 == -1)
//         error_msg("fork");
//     child_2 = fork();
//     if (child_2 == 0)
// {
//         if (dup2(ends[0], 0) == -1 || dup2(out_fd, 1) == -1)
//         error_msg("dup2");
//         close(ends[0]);
//         close(ends[1]);
//         close(in_fd);
//         close(out_fd);
//         exec(cmd2, env);
//         exit(EXIT_FAILURE);
//     }
//     else if (child_2 == -1)
//         error_msg("fork");
//     // Add after creating both child processes:
//     close(ends[0]);
//     close(ends[1]);
//     waitpid(child_1, NULL, 0);
//     waitpid(child_2, NULL, 0);
// }
