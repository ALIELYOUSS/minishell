#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <readline/readline.h>


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


typedef struct env_s
{
    char *key;
    char *value;
    struct env_s *next;
}   t_env;

typedef struct  mini_s
{
    char *cmd;
    char *flag;
    t_env *env;
} t_mini;

typedef struct  cmd_s
{
    char **cmd;
    char **flag;
    int fd_in;
    int fd_out;
    int pipe[2];
} t_cmd;

void  exec(t_env *env, char *prompt);
char *env_path(t_env *env, char *key);
void    ft_cd(char *prompt, t_env *env);
t_env *fill_env_list(char **envp);
t_env *create_env_node(const char *var);
void    ft_pwd();
void    ft_env(t_env *env);
void    ft_echo(char **str);
void    error_msg(char *str);
int     td_len(char **str);
void    ft_exit(t_env *env);

#endif