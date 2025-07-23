/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:00:00 by alel-you          #+#    #+#             */
/*   Updated: 2025/07/23 19:28:29 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# ifndef EXIT_STATUS
#  define EXIT_STATUS

#  define GET     0
#  define SET     1
#  define FREE    2
#  define EXIT  3

extern int	g_sig;

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
	CMD
}	t_type;

typedef struct s_hrdoc
{
	int		*fd;
	int		size;
}	t_hrdoc;

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
	void				*address;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_redir
{
	t_type				type;
	char				*file;
	int					fd;
	struct s_redir		*next;
	int					f;
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

/*============================ CLEANERS ===============================*/

void		close_all(int flag);
void		clear_all(int flag);
void		setup_signals(void);
void		sig_handler(int sig_num);

/*============================ EXECUTION ================================*/

void		exec_cmd(t_cmd *cmd_list, t_env *env_list, char **env,
				t_exec *exec);
void		handle_cmd(t_cmd *cmd_list, t_env *env_list, char **env);
void		init_pipe_ends(t_exec **exec_var);
void		dup_fd(t_cmd *cmd_node, int *index, t_exec *exec_var);
void		close_wait(int *p, int p_size, int *children);
char		*return_path(char *cmd, t_env *env_list);
char		*add_cmd_to_path(char *path, char *cmd);
int			is_builtin(char *prompt);
int			handle_builtin(t_cmd *cmd_list, t_env **env);
void		help_exec_command(char *cmd, t_env *env_list, char **env);
int			valid_cmd(t_cmd *cmd);
char		**handle_empty_env(void);
int			handle_command_not_found(char **args);
void		exec_error_case(char *cmd, int flag);
void		abs_path(char **command, char **env);
void		expander_helper_2(t_redir **tmp,
				t_env **env_lst, int *index, int *i);

/*==================== REDIRECTION & HEREDOC ============================*/

char		*exit_expand_2(t_redir **tmp, int *i);
void		handle_redir(t_cmd **cmd_list);
int			open_file(t_cmd **cmd, t_env *env_list);
int			herdoc_handler(char *delimiter, t_env *env_list);
int			is_type(t_cmd *cmd_list, t_type to_find);
char		*here_doc_expansion(char *input, t_env *env);
int			expander_2(t_redir **tmp, t_env **env_lst, int *index, int *i);
void		expander_helper_2(t_redir **tmp, t_env **env_lst,
				int *index, int *i);
void		expand_files(t_cmd **tmp, t_env **env_lst, int *f_index);
void		expand_norm(t_cmd **tmp, t_env **env_lst, int *index);

/*============================== BUILTINS ===============================*/

int			ft_echo(char **str, int fd);
int			ft_cd(char **args, t_env **env);
int			ft_pwd(char **cmd, int fd);
int			ft_exit(char **args);
int			ft_env(t_env *env, int fd);
int			ft_export(char *cmd, t_env *env, char **arg, int fd);
int			handle_unset(char **args, t_env **env);
int			is_valid_number(char *s);
void		error_chdir(int chdir_return);
void		handle_cd_tilde(t_env *env);
void		handle_cd_dash(t_env *env);
void		check_cd_args(char *path, t_env *env);
int			valid_identifier(char *key);
int			valid_identifier2(char *arg);
int			check_identifier(char *key);
void		process_echo_line(char *str, int fd);
int			is_valid_identifier(char *str);
void		print_env(t_env *env, char *s, int fd);
void		normal_add(t_env *env, char *key);
char		*retrieve_key(char *cmd);
int			invalid_key_msg(char *key, int *i);
int			handle_env(char **args, t_env *env_list, int fd);

/* ============================= PARSING ================================ */

void		add_var(t_env **env, char *key, char *value, int f);
int			tokenizer(t_list *tokens, char *content, int *i);
void		redir_and_hrdc(t_list *tokens, char *content, int *i);
void		tokenizer_helper(t_list *tokens, char *content, int *i);
t_tokens	*create_token(void *content, int t);
void		add_node(t_list *tokens, t_tokens *token);
void		clear_list(t_list *tokens);
int			found_quotes(char *content, int *i);
int			found_quotes_helper(char *content, int *i, int *tmp, char c);
int			for_word(char c);
char		*get_word(char *str, int *index);
char		*str_trim(char *str);
int			is_redir(t_tokens *token);
int			left_p(t_tokens **token, t_list **tokens, int *flag);

/*====================== SYNTAX =========================*/

int			syntax_errors(t_list *tokens);
void		syntax_error_msg(t_list *tokens);
int			parenthese(t_tokens *token);
int			multi_parenth(t_list *tokens, t_tokens *token, int *flag);
int			parenthese_se(t_list *tokens, t_tokens *token, int *flag);
int			closed_parenthese(t_tokens *token);
t_cmd		*build_cmd(t_list *tokens);
t_cmd		*new_cmd(char *content, t_redir *redir, t_type type);
void		add_cmd(t_cmd **cmd, t_cmd *new);
t_cmd		*last_cmd(t_cmd **cmd);
int			simple_cmd(int *f, t_tokens **token, t_cmd **cmd);
int			build_redir(int *f, t_tokens **token, t_cmd **cmd);
int			build_cmd_helper(t_tokens **token, t_cmd **cmd, int *f);
void		assign_node(t_cmd *node, t_redir *redir, t_type type);
t_redir		*new_redir(char *content, t_type type);
void		add_redir(t_cmd **cmd, t_redir *new);
t_redir		*last_redir(t_redir *redir);
void		split_cmd(t_cmd **cmd);
char		**args(char *cmd);
int			arr_size(char *cmd);
char		*splited(char *cmd, int *index);
int			arg_size(char *cmd, int *index);
int			loop_quote(char *cmd, int *index, char c);

/*============================ EXPANSION ================================*/

void		expansion(t_cmd *cmd, t_env *env_lst);
int			expander(t_cmd **tmp, t_env **env_lst, int *index, int *i);
char		*simple_join(char *s1, char *s2);
char		*bef_param(char *cmd, int *index);
char		*var_name(char *content, int *index, int *end);
int			var_len(char *str, int *len);
int			found_var(t_env *env, char *var_name);
char		*var_value(char *var_name, t_env *env);
char		*exit_expand(t_cmd **tmp, int *i);
int			export_quoting(char **arg, int *i);

/*======================== ENVIRONMENT HANDLING =========================*/

t_env		*fill_env_list(char **envp);
t_env		*create_env_node(char *var);
t_env		*find_var(t_env *env, char *key);
t_env		*new_env_node(char *key, char *value, int *f);
t_env		*env_dup(t_env *env);
t_env		**add_env(t_env **env, t_env *new);
void		sort_env(t_env **env);
void		new_value(t_env *e_tmp, char *value, int f);
char		*env_path(t_env *env, char *key );
void		change_current_path(t_env **env);
void		change_old_path(t_env **env_list, char *old_path);
void		add_exit_status(t_env **env, int exit_status);
int			get_exit_status(int exit_st, int flg);

/*========================== MEMORY MANAGEMENT =========================*/

char		**leak_killer(char *str, int flag);
char		**set_pwd_get(int flag, char *pwd);

/*========================== GARBAGE COLLECTION ========================*/

void		*ft_malloc(int size);
void		garbage_collector(t_garbage **garbage, void *address);
t_garbage	**get_garbage_head(t_garbage *gb_list_head, int flag);
void		free_garbage(t_garbage **garbage);

/*============================== UTILS =================================*/

char		*join_with_val(char *tmp1, char *tmp2, char *val);
char		*join_without_val(char *tmp1, char *tmp2);
int			ft_find_pos(char *s);
int			has_quotes(char *str);
char		*remove_quotes_from_delimiter(char *delimiter);
char		*process_heredoc_line(char *input, t_env *env_list,
				int should_expand);
int			pipe_counter(t_cmd *list);
int			simple_helper(int *f, t_tokens **token, t_cmd **cmd);
int			ft_break(char *prompt);
int			ft_isspace(char c);
int			finish_prompt(char *prompt);
void		expansion_helper(char *s, int *index, char c);
void		flag_quotes(char *cmd, int *flag);
int			quotes_ps(char *cmd);
char		*replace_quotes(char *cmd);
void		remove_quotes(t_cmd *cmd);
void		quote_case(char *arg, char *cmd, int *index, int *i);
void		quote_case(char *arg, char *cmd, int *index, int *i);
void		handle_export_value_helper(char *cmd, int *i, int *f);
void		handle_export_value_cases(t_env **e_tmp, char *value, int *f);
void		increment_helper(int *i, int *size);
int			check_cmd(char *cmd, int *i, int *count);
int			ispipe(t_tokens *token);
t_type		prev_node(t_list *tokens, t_tokens *token);
void		error_msg(char *msg);
void		rq_strcpy(char *cmd, char *final_cmd);
void		print_it(char *key, char *value, int fd);

/*========================== LIBFT WAPEANONS ============================*/

char		*join_it(char *s1, char *s2);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2, size_t n);
int			ft_strlen(char *str);
char		*ft_strdup(char *s1);
char		*ft_strchr(char *s, int c);
char		*ft_substr(char *s, int start, int len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_itoa(int a);
int			ft_atoi(char *str);
char		**ft_split(char *s, char c);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_bzero(void *s, size_t n);

#endif
