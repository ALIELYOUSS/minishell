/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:25:41 by yael-maa          #+#    #+#             */
/*   Updated: 2025/05/20 01:57:53 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>

typedef enum e_type
{
	WORD,
	OUT,
	IN,
	APP,
	HRDOC,
	AND,
	OR,
	PIPE,
	LP,
	RP,
}	t_type;

typedef struct s_tokens
{
	t_type				type;
	char				*content;
	struct s_tokens		*next;
}	t_tokens;

typedef struct s_list
{
	t_tokens	*head;
	t_tokens	*tail;
	int			size;
}	t_list;

typedef struct s_garbage
{
	void					*ptr;
	t_list					*tokens;
	struct s_garbage		*next;
}	t_garbage;

int			ft_strlen(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_break(char *prompt);
int			ft_isspace(char c);
int			ft_break(char *prompt);
int			finish_prompt(char *prompt);
void		ft_bzero(void *s, size_t n);
void		add_node(t_list *tokens, t_tokens *token);
t_tokens	*create_token(void *content, int t);
char		*get_word(char *str, int *index);
char		*join_it(char *s1, char *s2, char c, int *index);
void		quotes_parse(t_list *tokens, char *prompt, int *i);
void		found_quotes(char *content, int *i);
void		print_list(t_list *tokens);
void		clear_list(t_list *tokens);
void		quotes_syntax_error(char *prompt);
int			for_word(char c);
int			delimiter(char *str, char *c);
char		*str_trim(char *str);
void		tokenizer(t_list *tokens, char *content, int *i);
void		redir_and_hrdc(t_list *tokens, char *content, int *i);
void		pipe_and_or(t_list *tokens, char *content, int *i);
void		tokenizer_helper(t_list *tokens, char *content, int *i);
void		garbage_collector(t_garbage **garbage, t_garbage *new);
t_garbage	*ft_lstlast(t_garbage **garbage);
t_garbage	*add_garbage(void *ptr, t_list *tokens);
int			ft_lstsize(t_garbage *garbage);
void		free_garbage(t_garbage *garbage);
void		syntax_error_msg(t_list *tokens);
int			find_token(t_tokens *tokens, t_type type);
int			operator(t_tokens *token);
int			its_token(t_tokens *tokens, t_type type);
t_type		prev_node(t_list *tokens, t_tokens *token);
int			pipe_se(t_list *tokens, t_tokens *token);
int			is_redir(t_tokens *token);
int			is_redir(t_tokens *token);
void		syntax_errors(t_list *tokens);
char		*ft_strdup(char *s1);
int			parenthese(t_tokens *token);
void		multi_parenth(t_list *tokens, t_tokens *token, int *flag);
void		parenthese_se(t_list *tokens, t_tokens *token, int	*flag);
int			closed_parenthese(t_tokens *token);

#endif
