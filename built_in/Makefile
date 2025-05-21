FILES = $(wildcard *.c) 

OBJS = $(FILES:.c=.o)

LIB = ../libft/libft.a

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

# LDFLAGS = -lreadline

all: $(NAME)

$(LIB):
    $(MAKE) -C libft

$(NAME): $(OBJS) $(LIB)
    $(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

%.o: %.c minishell.h
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    $(MAKE) -C libft clean
    rm -f $(OBJS)

fclean: clean
    $(MAKE) -C libft fclean
    rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re