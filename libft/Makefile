NAME	=		libft.a

SRCS	=		./ft_atoi.c \
				./ft_isalpha.c \
				./ft_isalnum.c \
				./ft_isascii.c \
				./ft_isdigit.c \
				./ft_isprint.c \
				./ft_memset.c \
				./ft_strlcpy.c \
				./ft_strlen.c \
				./ft_bzero.c \
				./ft_tolower.c \
				./ft_toupper.c \
				./ft_memcpy.c \
				./ft_memccpy.c \
				./ft_strdup.c \
				./ft_strnstr.c \
				./ft_strncmp.c \
				./ft_memcmp.c \
				./ft_memchr.c \
				./ft_memmove.c \
				./ft_strchr.c \
				./ft_strrchr.c \
				./ft_strlcat.c \
				./ft_calloc.c \
				./ft_putchar_fd.c \
				./ft_putnbr_fd.c \
				./ft_putstr_fd.c \
				./ft_putendl_fd.c \
				./ft_strjoin.c \
				./ft_substr.c \
				./ft_split.c \
				./ft_strmapi.c \
				./ft_strtrim.c \
				./ft_itoa.c \
				./ft_lstnew.c \
				./ft_lstsize.c \
				./ft_lstadd_front.c \
				./ft_lstlast.c \
				./ft_lstadd_back.c \
				./ft_lstdelone.c \
				./ft_lstclear.c \
				./ft_lstiter.c \
				./ft_lstmap.c \
				./ft_intlen.c \
				./ft_putunbr_fd.c \
				./ft_uintlen.c \
				./ft_strrev.c \
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
				./ft_fill_struct.c \
				./get_next_line.c \
				./get_next_line_utils.c 


OBJS		=	$(SRCS:.c=.o)

CC			=	gcc

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
