NAME = pipex
SRCS = $(wildcard *.c) ../utils.c ../execution/exec.c
OBJS = $(SRCS:.c=.o)
LIB = ../libft/libft.a
CFLAGS = -Wall -Werror -Wextra -g
CC = cc

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

$(LIB):
	@make -C ../libft

clean:
	rm -f $(OBJS)
	make clean -C ../libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ../libft

re: fclean all

.PHONY: clean