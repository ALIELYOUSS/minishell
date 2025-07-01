/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:06:06 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/01 03:40:47 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clear_list(t_list *tokens)
{
	t_tokens	*tmp;
	while (tokens->head)
	{
		tmp = tokens->head;
		tokens->head = tokens->head->next;
		if (tmp->content)
		{
			free(tmp->content);
			tmp->content = NULL;
		}
		if (tmp)
			free(tmp);
		tokens->size--;
		tmp = NULL;
	}
	tokens = NULL;
}

int	delimiter(char *str, char *c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) || !for_word(str[i]) || str[i] == '"' || str[i] == '\'')
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

void	print_list(t_list *tokens)
{
	t_tokens	*tmp;

	tmp = tokens->head;
	while (tmp != tokens->tail)
	{
		printf("---------------content------------- :%s\n", tmp->content);
		printf("---------------type------------- :%d\n", tmp->type);
		tmp = tmp->next;
	}
	printf("-------------content------------ :%s\n", tmp->content);
	printf("---------------type------------- :%d\n", tmp->type);
}

void	print_cmd_list(t_cmd *cmd)
{
	t_cmd *tmp = cmd;
	while (tmp)
	{
		if (tmp->cmd)
			printf("cmd: %s\n", tmp->cmd);
		else if (tmp->redir->type == HRDOC)
			printf("%s\n", tmp->redir->file);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **env)
{
	char			*prompt;
	static char		*content;
	t_list			tokens;
	t_cmd			*cmd;
	t_env			*env_list;
	int				i;
	// int				f;

	(void)ac;
	(void)av;
	// f = 0;
	tokens.size = 0;
	ft_bzero(&tokens, sizeof(t_list));
	env_list = fill_env_list(env);
	while (1)
	{
		setup_signals();
		prompt = readline("~/minishell$ ✗ ");
		if (!finish_prompt(prompt))
			break ;
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
		tokenizer(&tokens, content, &i);
		free(content);
		syntax_errors(&tokens);
 		cmd = build_cmd(&tokens);
		expansion(cmd, env_list);
		// if (f == 1)
		// {
		// 	// t_env *envt = env_list;
		// 	// while (envt)
		// 	// {
		// 	// 	printf("before============%s=%s\n", envt->key,envt->value);
		// 	// 	envt = envt->next;
		// 	// }
		// 	return (0);
		// }
		remove_quotes(cmd);
		open_file(cmd);
		if (!pipe_counter(cmd) && is_type(cmd, HRDOC))
		{
			// f++;
			exec_heredoc_cmd(cmd, env, env_list);
		}
		else
		{
			// f++;
			execution(cmd, env, env_list);
		}
		if (tokens.size)
			clear_list(&tokens);
	}
	if (tokens.size)
		clear_list(&tokens);
	return (0);
}