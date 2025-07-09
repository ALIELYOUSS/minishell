/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:06:06 by yael-maa          #+#    #+#             */
/*   Updated: 2025/07/09 02:22:42 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void clear_list(t_list *tokens)
{
	t_tokens *tmp;
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

int delimiter(char *str, char *c)
{
	int i;

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

void print_list(t_list *tokens)
{
	t_tokens *tmp;

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

void print_cmd_list(t_cmd *cmd)
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

void print_envp(t_env *env)
{
	t_env *tmp = env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		else
			printf("%s\n", tmp->key);
		// else if(tmp->value)
		tmp = tmp->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (!tmp->redir)
			printf("1111111111111111111111111111\n");
		if (tmp->cmd)
			printf("=====%s\n", tmp->cmd);
		else
		{
			t_redir	*redir = tmp->redir;
			while (redir)
			{
				printf("type=====%d\n", redir->type);
				printf("file=====%s\n", redir->file);
				redir = redir->next;
			} 
		}
		tmp = tmp->next;
	}
}

int g_sig;

int main(int ac, char **av, char **env)
{
	char *prompt;
	static char *content;
	t_list tokens;
	t_cmd *cmd;
	t_env *env_list;
	t_hrdoc *hrd_fds;
	char **my_env;
	int	f;
	int i;

	(void)ac;
	(void)av;
	my_env = env;
	g_sig = 0;
	tokens.size = 0;
	hrd_fds = malloc(sizeof(t_hrdoc));
	ft_bzero(&tokens, sizeof(t_list));
	env_list = NULL;
	if (!my_env || !*env)
		my_env = handle_empty_env();
	env_list = fill_env_list(my_env);
	if (!isatty(0))
		return (0);
	int std_in = dup(0);
	set_get_hrd(SET, &hrd_fds);
	while (1)
	{
		dup2(std_in, 0);
		g_sig = 0;
		setup_signals();
		prompt = readline("~/minishell$ ✗🤯✗ ");
		// if (!finish_prompt(prompt))
		// 	break;
		if (!prompt)
			break ;
		add_history(prompt);
		content = str_trim(prompt);
		free(prompt);
		if (!content || !*content)
		{
			free(content);
			continue;
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
			continue;
		}
		hrd_fds->size = size_hrdoc(tokens.head);
		here_doc(&tokens, env_list, &hrd_fds);
		cmd = build_cmd(&tokens);
		// print_cmd(cmd);
		// exit(0);
		if (cmd)
		{
			open_file(&cmd);
			expansion(cmd, env_list);
			split_cmd(&cmd);
			remove_quotes(cmd);
			handle_cmd(cmd, env_list, env);
			clear_cmd(cmd);
		}
		set_get_hrd(FREE, &hrd_fds);
		if (tokens.size)
			clear_list(&tokens);
	}
	if (!env)
		free_td(my_env);
	free_env_list(env_list);
	if (tokens.size)
		clear_list(&tokens);
	if (hrd_fds)
		free(hrd_fds);
	return (get_exit_status(0, GET));
}
