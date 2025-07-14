/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:00:00 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/14 18:49:58 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>

# ifndef EXIT_STATUS
#  define EXIT_STATUS

extern int	g_sig;

#  define GET  0
#  define SET  1
#  define FREE 2

# endif

typedef enum e_type
{
	WORD,
	OUT,
	IN,
	APP,
	HRDOC,
	PIPE,
	LP,
	RP,
	CMD,
}	t_type;

typedef struct s_hrdoc
{
	int	*fd;
	int	size;
}	t_hrdoc;

typedef struct s_tokens
{
	t_type			type;
	char			*content;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_list
{
	t_tokens	*head;
	t_tokens	*tail;
	int			size;
}	t_list;

typedef struct s_redir
{
	t_type			type;
	char			*file;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct env_s
{
	char			*key;
	char			*value;
	int				f;
	struct env_s	*next;
}	t_env;

typedef struct s_cmd
{
	t_type			type;
	char			*cmd;
	char			**arg;
	t_redir			*redir;
	int				in;
	int				out;
	int				hrd;
	int				f;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_variables
{
	unsigned int	i;
	unsigned int	x;
	unsigned int	n;
	unsigned int	len;
	unsigned int	words;
	char			**sp;
}	t_var;

typedef struct s_exec
{
	int		num_cmds;
	int		*pipe_fds;
	pid_t	*children;
}	t_exec;

typedef struct s_garbage
{
	void				*address;
	struct s_garbage	*next;
}	t_garbage;

/// howa hada

int			is_valid_number(char *s);
char		**handle_empty_env(void);
int			has_quotes(char *str);
char		*process_heredoc_line(char *input, t_env *env_list,
				int should_expand);
char		*remove_quotes_from_delimiter(char *delimiter);
char		*join_with_val(char *tmp1, char *tmp2, char *val);
char		*join_without_val(char *tmp1, char *tmp2);
int			ft_find_pos(char *s);
int			char_state(char c);
t_hrdoc		**set_get_hrd(int flag, t_hrdoc **hrd_fds);
void		handle_cmd(t_cmd *cmd_list, t_env *env_list, char **env);
int			ft_strcmp(char *s1, char *s2);
char		*ft_substr(char *s, int start, int len);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
char		*ft_strchr(char *s, int c);
char		**ft_split(char *s, char c);
char		*ft_strjoin(char *s1, char *s2);
int			ft_export(char *cmd, t_env *env, char **arg, int fd);
int			ft_env(t_env *env, int fd);
int			ft_echo(char **str, int fd);
int			ft_cd(char *prompt, t_env **env);
int			ft_pwd(void);
int			ft_exit(char *args, t_env *env_list);
int			handle_echo(t_cmd *cmd_list);
int			exit_status(int exit_status);
void		change_current_path(t_env **env);
void		change_old_path(t_env **env_list, char *old_path);
void		exec_cmd(t_cmd *cmd_list, t_env *env_list,
				char **env, t_exec *exec);
int			get_exit_status(int exit_st, int flg);
t_cmd		**get_current_cmd(int flag, t_cmd **cmd);
int			handle_unset(char *prompt, t_env **env);
void		add_exit_status(t_env **env, int exit_status);
char		*here_doc_expansion(char *input, t_env *env);
int			is_upper(char *str);
void		close_wait(int *p, int p_size, int *children);
char		*add_cmd_to_path(char *path, char *cmd);
void		handle_redir(t_cmd **cmd_list);
void		dup_fd(t_cmd *cmd_node, int *index, t_exec *exec_var);
void		init_pipe_ends(t_exec **exec_var);
void		help_exec_command(char *cmd, t_env *env_list, char **env);
char		*return_path(char *cmd, t_env *env_list);
int			execution(t_cmd *cmd_list, char **env, t_env **env_list);
void		here_doc_handler(int sig_num);
void		setup_signals(void);
void		setup_hrdoc_signals(void);
int			pipe_counter(t_cmd *list);
int			is_builtin(char *prompt);
int			is_parent_builtin(char *prompt);
int			handle_builtin(t_cmd *cmd_list, t_env **env);
void		error_msg(char *msg);
void		handel_redect(t_cmd *cmd);
void		exec(char *prompt, t_env *env, char **env_p);
char		*env_path(t_env *env, char *key);
t_env		*fill_env_list(char **envp);
t_env		*create_env_node(char *var);
int			td_len(char **str);
void		free_td(char **str);
void		free_env_list(t_env *env);
int			size_hrdoc(t_tokens *tokens_list);
int			save_stdin(void);
void		sig_handler(int sig_num);
char		*ft_itoa(int a);
int			ft_atoi(char *str);
char		*here_doc_expansion(char *input, t_env *env);
void		set_hrdoc_fd(t_cmd *cmd, t_env *env_list, t_list *token);
char		*find_delimiter(t_cmd *cmd_list, t_type to_find);
int			herdoc_handler(char *delimiter, t_env *env_list);
int			is_type(t_cmd *cmd_list, t_type to_find);
void		expansion_helper(char *s, int *index, char c);
int			ispipe(t_tokens *token);
int			ft_strlen(char *str);
int			ft_strncmp(char *s1, char *s2, size_t n);
int			ft_break(char *prompt);
int			ft_isspace(char c);
int			finish_prompt(char *prompt);
void		ft_bzero(void *s, size_t n);
void		add_node(t_list *tokens, t_tokens *token);
t_tokens	*create_token(void *content, int t);
char		*get_word(char *str, int *index);
int			found_quotes(char *content, int *i);
int			found_quotes_helper(char *content, int *i, int *tmp, char c);
void		print_list(t_list *tokens);
void		clear_list(t_list *tokens);
void		quotes_syntax_error(void);
int			for_word(char c);
int			delimiter(char *str, char *c);
char		*str_trim(char *str);
int			tokenizer(t_list *tokens, char *content, int *i);
void		redir_and_hrdc(t_list *tokens, char *content, int *i);
void		pipe_and_or(t_list *tokens, char *content, int *i);
void		tokenizer_helper(t_list *tokens, char *content, int *i);
void		zgarbage_collector(t_garbage **garbage, t_garbage *new);
t_garbage	*ft_lstlast(t_garbage **garbage);
t_garbage	*add_garbage(void *ptr, t_list *tokens);
int			ft_lstsize(t_garbage *garbage);
void		free_garbage(t_garbage *garbage);
void		syntax_error_msg(t_list *tokens);
int			find_token(t_tokens *tokens, t_type type);
int			its_token(t_tokens *tokens, t_type type);
t_type		prev_node(t_list *tokens, t_tokens *token);
int			is_redir(t_tokens *token);
void		here_doc(t_list *tokens, t_env *env_list);
int			syntax_errors(t_list *tokens);
char		*ft_strdup(char *s1);
int			parenthese(t_tokens *token);
int			multi_parenth(t_list *tokens, t_tokens *token, int *flag);
int			parenthese_se(t_list *tokens, t_tokens *token, int *flag);
int			closed_parenthese(t_tokens *token);
t_cmd		*new_cmd(char *content, t_redir *redir, t_type type);
void		add_cmd(t_cmd **cmd, t_cmd *new);
t_cmd		*last_cmd(t_cmd **cmd);
char		*join_it(char *s1, char *s2);
void		add_redir(t_cmd **cmd, t_redir *new);
t_redir		*new_redir(char *content, t_type type);
t_redir		*last_redir(t_redir *redir);
t_cmd		*build_cmd(t_list *tokens);
void		clear_cmd(t_cmd *cmd);
void		clear_directions(t_redir *redir);
void		remove_quotes(t_cmd *cmd);
char		*replace_quotes(char *cmd);
void		flag_quotes(char *cmd, int *flag);
int			quotes_ps(char *cmd);
void		expansion(t_cmd *cmd, t_env *env_lst);
char		*simple_join(char *s1, char *s2);
char		*bef_param(char *cmd, int *index);
int			found_var(t_env *env, char *var_name);
char		*var_value(char *var_name, t_env *env);
int			var_len(char *str, int *len);
char		*var_name(char *content, int *index, int *end);
void		open_file(t_cmd **cmd, t_env *env_list);
int			build_redir(int *f, t_tokens **token, t_cmd **cmd);
int			simple_cmd(int *f, t_tokens **token, t_cmd **cmd);
int			build_cmd_helper(t_tokens **token, t_cmd **cmd, int *f);
int			expander(t_cmd **tmp, t_env **env_lst, int *index, int *i);
char		*var_value(char *var_name, t_env *env);
int			left_p(t_tokens **token, t_list **tokens, int *flag);
void		split_cmd(t_cmd **cmd);
char		**args(char *cmd);
int			arr_size(char *cmd);
char		*splited(char *cmd, int *index);
int			arg_size(char *cmd, int *index);
int			loop_quote(char *cmd, int *index, char c);
void		handle_export_value_helper(char *cmd, int *i, int *f);
char		*retrieve_key(char *cmd);
int			valid_identifier(char *key);
void		print_env(t_env *env, char *s, int fd);
void		normal_add(t_env *env, char *key);
void		add_var(t_env *env, char *key, char *value, int f);
t_env		*find_var(t_env *env, char *key);
void		handle_export_value_cases(t_env **e_tmp, char *value, int *f);
int			check_identifier(char *key);
void		increment_helper(int *i, int *size);
void		quote_case(char *arg, char *cmd, int *index, int *i);
int			check_cmd(char *cmd, int *i, int *count);
t_env		*env_dup(t_env *env);
t_env		*new_env_node(char *key, char *value, int *f);
t_env		**add_env(t_env **env, t_env *new);
void		sort_env(t_env **env);
void		new_value(t_env *e_tmp, char *value, int f);
char		**ft_freearr(char **arr);

#endif
