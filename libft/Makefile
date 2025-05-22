# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 21:17:16 by alel-you          #+#    #+#              #
#    Updated: 2024/11/20 01:54:53 by alel-you         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = ft_isascii.c    ft_memmove.c    ft_split.c      ft_strlcat.c \
 ft_atoi.c       ft_isdigit.c    ft_memset.c     ft_strchr.c     ft_strlcpy.c    ft_strtrim.c \
 ft_bzero.c      ft_isprint.c    ft_putchar_fd.c  ft_strlen.c     ft_substr.c    ft_strrchr.c\
 ft_calloc.c     ft_itoa.c       ft_putendl_fd.c ft_strdup.c     ft_strmapi.c    ft_toupper.c \
 ft_isalnum.c    ft_memcmp.c 	ft_striteri.c   ft_strncmp.c	ft_strnstr.c   ft_memchr.c \
 ft_isalpha.c    ft_memcpy.c     ft_putstr_fd.c  ft_strjoin.c 	 ft_tolower.c  ft_putnbr_fd.c \

BONUS_FILES = ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstsize_bonus.c 	ft_lstadd_front_bonus.c \
				ft_lstdelone_bonus.c	 ft_lstmap_bonus.c    ft_lstadd_back_bonus.c  ft_lstnew_bonus.c  ft_lstlast_bonus.c \
				
OBJF = $(FILES:.c=.o)

BONUS_OBJF = $(BONUS_FILES:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror

NAME = libft.a

all: $(NAME)


$(NAME): $(OBJF)
	@ar rc $(NAME) $(OBJF)
	@echo libft.a created

%.o: %.c libft.h
	@$(CC) $(FLAGS) -c $< -o $@

bonus: $(BONUS_OBJF)
	@ar rc $(NAME) $(BONUS_OBJF)
	@echo BONUS_obj created

clean:
	@rm -rf $(OBJF) $(BONUS_OBJF)
	@echo CLEANED

fclean: clean
	@rm -rf $(NAME)
	@echo FCLEAN CALLED
	
re: fclean all

.PHONY: clean