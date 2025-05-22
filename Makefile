NAME = minishell
SRCS = $(wildcard built_in/*.c) main.c
OBJS = $(SRCS:.c=.o)
LIB = libft/libft.a
CFLAGS = -Wall -Werror -Wextra -g 
RFLAG = -lreadline
CC = cc

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) $(RFLAG) -o $(NAME)

$(LIB):
	@make -C ./libft

clean:
	rm -f $(OBJS)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft