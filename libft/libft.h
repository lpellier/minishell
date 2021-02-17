/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaspellier <lucaspellier@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:15:06 by lpellier          #+#    #+#             */
/*   Updated: 2020/03/25 21:09:40 by lucaspellie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define CONVERTER "ciduxXps%"
# define BUFFER_SIZE 32
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct		s_printf
{
	int				width;
	int				number;
	int				precision;
	int				padding;
	int				outputlen;
	int				plus;
	int				minus;
	int				space;
	int				perc;
	int				count;
	int				len;
	int				orig;
	char			type;
}					t_printf;

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),\
					void (*del)(void *));
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_bzero(void *s, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putunbr_fd(unsigned int n, int fd);
void				ft_putnnbr_fd(int n, int size, int fd);
void				ft_putnstr_fd(char *s, int size, int fd);
char				*ft_strrev(char *str);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strnstr(const char *haystack, const char *needle,\
					size_t len);
char				*ft_substr(const char *s, unsigned int start, size_t len);
char				*ft_strdup(const char *s1);
char				*ft_strchr(const char *s, int c);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(const char *s1, const char *set);
char				*ft_itoa(int n);
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char				**ft_split(const char *s, char c);
int					ft_lstsize(t_list *lst);
int					ft_intlen(long n);
int					ft_uintlen(unsigned long n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_strlen(const char *s);
int					ft_toupper(int c);
int					ft_atoi(const char *str);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_tolower(int c);
char				*ft_int_hexmin(long n, char *tab);
char				*ft_int_hexmax(long n, char *tab);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				digit_count(long value, int base);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);

const char			*checkwidth(const char *format, t_printf *info, va_list ap);
const char			*checkprecision(const char *format, t_printf *info, \
					va_list ap);
const char			*checktype(const char *format, t_printf *info);
const char			*ft_fill_struct(const char *format, t_printf *info, \
					va_list ap);
int					count_format(const char *format);
void				output_flags(t_printf *info);
int					output_sign(t_printf *info, int res);
void				put_zeros(t_printf *info);
void				output_string(t_printf *info, va_list ap);
void				output_int(t_printf *info, va_list ap);
void				output_uint(t_printf *info, va_list ap);
void				output_char(t_printf *info, va_list ap);
void				output_adress(t_printf *info, va_list ap);
void				output_hexmin(t_printf *info, va_list ap);
void				output_hexmax(t_printf *info, va_list ap);
const char			*print_before(const char *format, t_printf *info);
const char			*print_aoutsider(const char *format, t_printf *info);
const char			*init_perc(t_printf *info, const char *format);
void				check_padding_case_int(t_printf *info, int res);
void				check_padding_case_adress(t_printf *info, void *res, \
					char *str);
void				check_padding_case_hex(t_printf *info, void *ret);
void				check_padding_case(t_printf *info);
void				ft_output(t_printf *info, va_list ap);

int					get_next_line(int fd, char **line);
int					check_n(char *stock);

int					ft_printf(const char *format, ...);


#endif
