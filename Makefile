# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucaspellier <lucaspellier@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/25 19:17:20 by lucaspellie       #+#    #+#              #
#    Updated: 2020/03/26 21:44:20 by lucaspellie      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #

NAME = minishell.a

LIBFT = libft/libft.a

FLAGS = -Wall -Werror -Wextra

SRCS = main.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C libft
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS)

clean :
	@rm -rf $(OBJS)
	@make clean -C libft

fclean : clean
	@rm -rf $(NAME)
	@rm -rf minishell
	@make fclean -C libft

re : fclean all
