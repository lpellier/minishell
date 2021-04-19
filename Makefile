# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/25 19:17:20 by lucaspellie       #+#    #+#              #
#    Updated: 2021/04/19 14:04:35 by lpellier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

CFLAGS = -Wall -Werror -Wextra -pedantic -g3

CC = clang

SRCS = srcs/main.c \
		srcs/built_in/built_in.c \
		srcs/built_in/built_in2.c \
		srcs/built_in/do_redir.c \
		srcs/built_in/do_pipe.c \
		srcs/built_in/do_export.c \
		srcs/built_in/binary_things.c \
		srcs/built_in/env_things.c \
		srcs/built_in/cmp_size_and_cmd.c \
		srcs/built_in/pure_shell.c \
		srcs/free/free.c \
		srcs/free/secure_free.c \
		srcs/skeleton/linked_lists.c \
		srcs/skeleton/create_and_push.c \
		srcs/skeleton/print_and_cmp.c \
		srcs/skeleton/structs.c \
		srcs/skeleton/struct_env.c \
		srcs/parsing/directories.c \
		srcs/parsing/parsing_utils.c \
		srcs/parsing/parsing_space.c \
		srcs/parsing/parsing.c \
		srcs/parsing/get_something.c \
		srcs/parsing/read_everything.c \
		srcs/parsing/char_and_key.c \
		srcs/parsing/colon_and_count.c \
		srcs/parsing/backsl_and_quote.c \
		srcs/parsing/control_and_dollar.c \
		srcs/shell_init/init.c \
		srcs/termcap/all_signal.c \
		srcs/termcap/termcap_utils.c \
		srcs/test/testing_func.c \
		srcs/redir_std.c

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
