cmake_minimum_required(VERSION 3.10)
project(42)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER /usr/bin/clang)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wall -Wextra")
SET(LIBFT_SRC
./libft/ft_isalpha.c
./libft/ft_itoa.c
./libft/ft_isalnum.c
./libft/ft_isascii.c  
./libft/ft_isdigit.c  
./libft/ft_isprint.c
./libft/ft_strlen.c
./libft/ft_bzero.c
./libft/ft_tolower.c
./libft/ft_strdup.c
./libft/ft_strndup.c
./libft/ft_strncmp.c
./libft/ft_strchr.c
./libft/ft_calloc.c  
./libft/ft_putchar_fd.c
./libft/ft_putchar.c
./libft/ft_putnbr_fd.c
./libft/ft_putstr_fd.c
./libft/ft_strjoin.c  
./libft/ft_substr.c  
./libft/ft_split.c
./libft/ft_intlen.c  
./libft/ft_putunbr_fd.c  
./libft/ft_uintlen.c
./libft/ft_int_hexmin.c  
./libft/ft_int_hexmax.c  
./libft/ft_putnnbr_fd.c  
./libft/ft_putnstr_fd.c  
./libft/digit_count.c  
./libft/ft_printf.c  
./libft/ft_output.c  
./libft/ft_output_other.c  
./libft/ft_utils_functions.c  
./libft/ft_auxiliary_functions.c  
./libft/ft_fill_struct.c  
./libft/get_next_line.c  
./libft/get_next_line_utils.c
        )

set(MINISHELL_SRC
<<<<<<< HEAD
        ./built_in.c
        ./built_in2.c
        ./init.c
        ./linked_lists.c
        ./free.c
        ./main.c
        ./parsing.c
        ./minishell.h
        ./all_signal.c
        ./redir_std.c

=======
        ./srcs/built_in/built_in.c
        ./srcs/built_in/built_in2.c
        ./srcs/shell_init/init.c
        ./srcs/linked_lists/linked_lists.c
        ./srcs/free/free.c
        ./srcs/main.c
        ./srcs/parsing/parsing.c
        ./srcs/parsing/parsing_utils.c
        ./srcs/parsing/directories.c
        ./srcs/parsing/read_everything.c
        ./srcs/parsing/str_manipulations.c
        ./includes/minishell.h
        ./srcs/termcap/all_signal.c
        ./srcs/termcap/termcap_utils.c
        ./srcs/test/testing_func.c
>>>>>>> lucas
        )
add_library(LIBFT
        ${LIBFT_SRC}
        )
add_executable(
        minishell
        ${MINISHELL_SRC}
)
target_link_libraries(
        minishell
        LIBFT
        termcap
)
include_directories(
        ./libft/
)