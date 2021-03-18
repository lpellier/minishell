# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/25 19:17:20 by lucaspellie       #+#    #+#              #
#    Updated: 2021/03/15 16:09:56 by lpellier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

CFLAGS = -Wall -Werror -Wextra -pedantic -g3

CC = clang

SRCS = parsing.c \
		built_in.c \
		built_in2.c \
		free.c \
		init.c \
		linked_lists.c \
		all_signal.c \
		main.c 

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C libft
	cp libft/libft.a ./$(NAME)
	$(CC) $(CFLAGS) -ltermcap $(SRCS) -o minishell $(LIBFT)

clean :
	rm -rf $(OBJS)
	make clean -C libft

fclean : clean
	rm -rf $(NAME)
	rm -rf minishell
	make fclean -C libft

re : fclean all
