SRC = src/parser/syntax_errors_utils.c src/parser/syntax_errors.c src/main.c src/utils/libft/libft_utils.c src/utils/libft/libft_utils1.c src/utils/prompt_utils.c src/tokenizer/get_word.c src/tokenizer/tokenize.c \
    src/utils/open_files.c src/expansion/expand.c src/utils/quotes_rem.c src/tokenizer/quotes_error.c src/cmd_builder/cmd_builder.c src/cmd_builder/redirections.c src/cmd_builder/cmd_builder_utils.c \
	execution/built_in/ft_cd.c execution/built_in/ft_echo.c execution/built_in/ft_env.c execution/built_in/ft_exit.c execution/built_in/ft_unset.c \
	execution/built_in/ft_export.c execution/built_in/ft_pwd.c execution/exec_cmd/exec_cmd.c \
	execution/redir/herdoc.c execution/redir/redirections.c \
	execution/signal_handler/signals.c execution/utils/libft_utils.c execution/utils/utils.c \
	execution/exec_cmd/utils/exec_utils_utils.c execution/exec_cmd/utils/exec_utils.c execution/exec_cmd/utils/exec_cmd_utils.c execution/redir/herdoc_expander.c \

OBJ = $(SRC:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror 

SANIT = -fsanitize=address -g3

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -L/usr/local/lib -I/usr/local/include -lreadline 

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:fclean all

.PHONY: clean