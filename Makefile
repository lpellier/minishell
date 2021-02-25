# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/25 19:17:20 by lucaspellie       #+#    #+#              #
#    Updated: 2021/02/25 11:57:09 by lpellier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell.a

LIBFT = libft/libft.a

FLAGS = -Wall -Werror -Wextra

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
	@ar rc $(NAME) $(OBJS)
	@gcc $(FLAGS) $(NAME) -o minishell 

clean :
	@rm -rf $(OBJS)
	@make clean -C libft

fclean : clean
	@rm -rf $(NAME)
	@rm -rf minishell
	@make fclean -C libft

re : fclean all
