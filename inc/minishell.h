/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:25:41 by yael-maa          #+#    #+#             */
/*   Updated: 2025/05/06 21:19:38 by yael-maa         ###   ########.fr       */
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
	t_list				*tokens;
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
void		syntax_error(char *prompt);
int			for_word(char c);
int			delimiter(char *str, char *c);
char		*str_trim(char *str);
void		tokenizer(t_list *tokens, char *content, int *i);
void		redir_and_hrdc(t_list *tokens, char *content, int *i);
void		pipe_and_or(t_list *tokens, char *content, int *i);
void		tokenizer_helper(t_list *tokens, char *content, int *i);
t_garbage	*add_garbage(void *ptr, t_list *tokens);
void		garbage_collector(t_garbage **garbage, t_garbage *new);
t_garbage	*ft_lstlast(t_garbage **garbage);
int			ft_lstsize(t_garbage *garbage);
void		free_garbage(t_garbage *garbage);

#endif
