/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 21:50:12 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/21 22:09:51 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig;

void	interpret_command(t_cmd **cmd_list, t_env **env_list, char **env)
{
	if (cmd_list && *cmd_list)
	{
		expansion(*cmd_list, *env_list);
		split_cmd(cmd_list);
		remove_quotes(*cmd_list);
		handle_cmd(*cmd_list, *env_list, env);
	}
}

int	process_tokens(t_list *tokens, t_cmd **cmd, t_env **env_list, char **env)
{
	if (!syntax_errors(tokens))
	{
		return (clear_all(CMD), 0);
	}
	*cmd = build_cmd(tokens);
	if (*cmd)
	{
		if (!valid_cmd(*cmd))
			return (clear_all(CMD), 0);
		if (!open_file(cmd, *env_list))
			return (clear_all(CMD), 0);
		interpret_command(cmd, env_list, env);
	}
	clear_all(CMD);
	return (1);
}

int	readline_loop_helper(t_list **tokens, t_env **env_list, char **my_env)
{
	t_cmd		*cmd;
	static char	*content;
	char		*prompt;
	int			i;

	cmd = NULL;
	prompt = NULL;
	i = 0;
	(*tokens)->size = 0;
	(*tokens)->head = NULL;
	prompt = readline("~/minishell$ ✗🤯✗ ");
	if (!prompt)
		return (-1);
	add_history(prompt);
	content = str_trim(prompt);
	i = 0;
	if (!content || (content && !*content)
		|| !tokenizer(*tokens, content, &i))
		return (0);
	process_tokens(*tokens, &cmd, env_list, my_env);
	return (1);
}

void	readline_loop(t_list *tokens, t_env **env_list, char **my_env)
{
	int			std_in;
	int			f;

	std_in = dup(0);
	while (1)
	{
		dup2(std_in, 0);
		g_sig = 0;
		setup_signals();
		f = readline_loop_helper(&tokens, env_list, my_env);
		if (f < 0)
			break ;
		else if (f == 0)
			continue ;
	}
	close(std_in);
}

int	main(int ac, char **av, char **env)
{
	t_list	tokens;
	t_env	*env_list;
	char	**my_env;

	(void)ac;
	(void)av;
	my_env = env;
	g_sig = 0;
	tokens.size = 0;
	ft_bzero(&tokens, sizeof(t_list));
	env_list = NULL;
	if (!my_env || !*env)
		my_env = handle_empty_env();
	env_list = fill_env_list(my_env);
	if (!env_list)
		return (0);
	readline_loop(&tokens, &env_list, my_env);
	clear_all(-42);
	get_garbage_head(NULL, FREE);
	return (get_exit_status(0, GET));
}
