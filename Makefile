# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/25 19:17:20 by lucaspellie       #+#    #+#              #
#    Updated: 2021/05/06 14:33:22 by tefroiss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

CFLAGS = -Wall -Werror -Wextra -pedantic -g3

CC = clang

SRCS = srcs/main.c \
		srcs/built_in/binary_things.c \
		srcs/built_in/built_in.c \
		srcs/built_in/built_in2.c \
		srcs/built_in/cd_things.c \
		srcs/built_in/cmp_size_and_cmd.c \
		srcs/built_in/do_export.c \
		srcs/built_in/echo_things.c \
		srcs/built_in/env_things.c \
		srcs/built_in/key_n_value_error.c \
		srcs/built_in/pure_shell.c \
		srcs/free/free.c \
		srcs/parsing/backsl_and_quote.c \
		srcs/parsing/char_and_int.c \
		srcs/parsing/char_and_key.c \
		srcs/parsing/colon_and_count.c \
		srcs/parsing/colon_count_split.c \
		srcs/parsing/control_and_dollar.c \
		srcs/parsing/directories.c \
		srcs/parsing/key_move.c \
		srcs/parsing/parsing_space.c \
		srcs/parsing/parsing_utils.c \
		srcs/parsing/parsing.c \
		srcs/parsing/error_handling.c \
		srcs/parsing/read_everything_suite.c \
		srcs/parsing/read_everything.c \
		srcs/parsing/redir_and_swap.c \
		srcs/parsing/transform.c \
		srcs/redir/do_pipe.c \
		srcs/redir/do_redir.c \
		srcs/redir/redir_std.c \
		srcs/shell_init/begin_shell.c \
		srcs/shell_init/init_info.c \
		srcs/shell_init/init.c \
		srcs/skeleton/print_and_cmp.c \
		srcs/skeleton/struct_env.c \
		srcs/skeleton/structs.c \
		srcs/termcap/all_signal.c \
		srcs/termcap/termcap_utils.c \
		srcs/termcap/termcap.c \
		srcs/test/testing_func.c

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
