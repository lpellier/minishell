# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/25 19:17:20 by lucaspellie       #+#    #+#              #
#    Updated: 2021/02/26 10:53:36 by lpellier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell.a

LIBFT = libft/libft.a

FLAGS = -Wall -Werror -Wextra -Weverything

SRCS = parsing.c \
		built_in.c \
		built_in2.c \
		free.c \
		init.c \
		linked_lists.c \
		main.c 

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C libft
	@cp libft/libft.a ./$(NAME)
	@clang $(FLAGS) $(SRCS) -o minishell 

clean :
	@rm -rf $(OBJS)
	@make clean -C libft

fclean : clean
	@rm -rf $(NAME)
	@rm -rf minishell
	@make fclean -C libft

re : fclean all
