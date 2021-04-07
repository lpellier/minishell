# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/06 14:29:46 by tefroiss          #+#    #+#              #
#    Updated: 2021/04/07 13:39:25 by tefroiss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=		libft.a

SRCS	=		./ft_isalpha.c \
				./ft_itoa.c \
				./ft_checkc.c \
				./ft_isalnum.c \
				./ft_isascii.c \
				./ft_isdigit.c \
				./ft_isprint.c \
				./ft_strlen.c \
				./ft_strncat.c \
				./ft_strcpy.c \
				./ft_bzero.c \
				./ft_tolower.c \
				./ft_strdup.c \
				./ft_strndup.c \
				./ft_strncmp.c \
				./ft_strncpy.c \
				./ft_calloc.c \
				./ft_strchr.c \
				./ft_putchar.c \
				./ft_putchar_fd.c \
				./ft_putnbr_fd.c \
				./ft_putstr_fd.c \
				./ft_strjoin.c \
				./ft_substr.c \
				./ft_split.c \
				./ft_intlen.c \
				./ft_strtrim.c \
				./ft_putunbr_fd.c \
				./ft_uintlen.c \
				./ft_int_hexmin.c \
				./ft_int_hexmax.c \
				./ft_putnnbr_fd.c \
				./ft_putnstr_fd.c \
				./digit_count.c \
				./ft_printf.c \
				./ft_output.c \
				./ft_output_other.c \
				./ft_utils_functions.c \
				./ft_auxiliary_functions.c \
				./ft_output_otherss.c \
				./ft_utils_fonctions_other.c \
				./ft_printf_utils.c \
				./ft_fill_struct.c \
				./get_next_line.c \
				./get_next_line_utils.c 


OBJS		=	$(SRCS:.c=.o)

CC			=	clang

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

CLEAN		=	clean

$(NAME)		:	$(OBJS)
				ar rc libft.a $(OBJS)

bonus		:	$(OBJS)
				ar rc libft.a $(OBJS)

all			:	$(NAME)

clean		:
				$(RM) $(OBJS)

fclean		:	clean
				$(RM) $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re bonus
