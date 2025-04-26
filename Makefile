SRC = src/*.c src/utils/libft/libft_utils.c src/utils/prompt_utils.c \

OBJ = $(SRC:.c=.o)

SRC_BONUS =

OBJ_BONUS = $(SRC_BONUS:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror

NAME = minishell

NAME_BONUS = minishell_bonus

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -I$HOME/.local/include -L$HOME/.local/lib -lreadline

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