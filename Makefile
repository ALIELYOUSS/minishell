SRC = src/syntax_errors/syntax_errors_utils.c src/syntax_errors/syntax_errors.c src/main.c src/utils/libft/libft_utils.c src/utils/prompt_utils.c src/tokenizer/get_word.c src/tokenizer/tokenize.c src/tokenizer/redirections.c\

OBJ = $(SRC:.c=.o)

SRC_BONUS =

OBJ_BONUS = $(SRC_BONUS:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror -fsanitize=address

NAME = minishell

NAME_BONUS = minishell_bonus

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -I$(HOME)/.local/include -L$(HOME)/.local/lib -lreadline

bonus: $(NAME_BONUS)

$(NAME_BONUS):
	$(CC) $(FLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re:fclean all

.PHONY: clean