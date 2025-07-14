/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:06:06 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/14 19:13:49 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		// if (tmp->content)
		// {
		// 	free(tmp->content);
		// 	tmp->content = NULL;
		// }
		if (tmp)
			free(tmp);
		tokens->size--;
		tmp = NULL;
	}
	tokens->head = NULL;
	tokens->tail = NULL;
}

int	delimiter(char *str, char *c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) || !for_word(str[i])
		 	|| str[i] == '"' || str[i] == '\'')
		{
			*c = str[i];
			return (0);
		}
		i++;
	}
	if (str[i] == '\0')
	{
		*c = '\0';
		return (0);
	}
	return (1);
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

int	g_sig;

void	interpret_command(t_cmd **cmd_list, t_env **env_list, char **env)
{
	if (cmd_list && *cmd_list)
	{
		open_file(cmd_list, *env_list);
		expansion(*cmd_list, *env_list);
		split_cmd(cmd_list);
		remove_quotes(*cmd_list);
		handle_cmd(*cmd_list, *env_list, env);
	}
}

int	main(int ac, char **av, char **env)
{
	static char	*content;
	char	*prompt;
	t_list	tokens;
	t_cmd	*cmd;
	t_env	*env_list;
	char	**my_env;
	int	std_in;
	int	f;
	int	i;

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
	std_in = dup(0);
	while (1)
	{
		dup2(std_in, 0);
		g_sig = 0;
		setup_signals();
		prompt = readline("~/minishell$ ✗🤯✗ ");
		if (!prompt)
			break ;
		add_history(prompt);
		content = str_trim(prompt);
		free(prompt);
		if (!content || !*content)
		{
			free(content);
			continue ;
		}
		i = 0;
		f = tokenizer(&tokens, content, &i);
		if (!f)
		{
			free(content);
			continue ;
		}
		free(content);
		if (!syntax_errors(&tokens))
		{
			clear_list(&tokens);
			continue ;
		}
		cmd = build_cmd(&tokens);
		interpret_command(&cmd, &env_list, env);
		if (tokens.size && tokens.head)
			clear_list(&tokens);
		if (cmd)
			clear_cmd(cmd);
	}
	if (!env)
		free_td(my_env);
	free_env_list(env_list);
	// if (tokens.size)
	// 	clear_list(&tokens);
	return (get_exit_status(0, GET));
}
