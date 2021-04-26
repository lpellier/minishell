/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:15:06 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/26 21:46:05 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define CONVERTER "ciduxXps%"
# define BUFFER_SIZE 32
# define PATH_MAX 4096
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}					t_list;

typedef struct s_printf
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

void				ft_bzero(void *s, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putunbr_fd(unsigned int n, int fd);
void				ft_putnnbr_fd(int n, int size, int fd);
void				ft_putnstr_fd(char *s, int size, int fd);
void				ft_strncat(char *dest, char *src, int nb);
void				ft_strcpy(char *dest, char *src);
void				manque_de_place(t_printf *printf, int padlength);
void				reduce_me(t_printf *printf, unsigned int res);
char				*ft_strncpy(char *dest, char *src, unsigned int n);
char				*ft_substr(const char *s, unsigned int start, size_t len);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s1, int size);
char				*ft_strchr(const char *s, int c);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(const char *s, char c);
int					ft_calloc(void **ptr, size_t count, size_t size);
int					ft_putchar(int c);
int					ft_intlen(long n);
int					ft_atoi(const char *str);
int					ft_uintlen(unsigned long n);
int					ft_checkc(char c, const char *set);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_strlen(const char *s);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_tolower(int c);
int					return_written(const char *format, t_printf *printf);
char				*ft_int_hexmin(long n, char *tab);
char				*ft_int_hexmax(long n, char *tab);
char				*ft_itoa(int n);
size_t				digit_count(long value, int base);

const char			*checkwidth(const char *format, t_printf *printf, \
					va_list ap);
const char			*checkprecision(const char *format, t_printf *printf, \
					va_list ap);
const char			*checktype(const char *format, t_printf *printf);
const char			*ft_fill_struct(const char *format, t_printf *printf, \
					va_list ap);
int					count_format(const char *format);
void				output_flags(t_printf *printf);
int					output_sign(t_printf *printf, int res);
void				put_zeros(t_printf *printf);
void				output_string(t_printf *printf, va_list ap);
void				output_int(t_printf *printf, va_list ap);
void				output_uint(t_printf *printf, va_list ap);
void				output_char(t_printf *printf, va_list ap);
void				output_adress(t_printf *printf, va_list ap);
void				output_hexmin(t_printf *printf, va_list ap);
void				output_hexmax(t_printf *printf, va_list ap);
const char			*print_before(const char *format, t_printf *printf);
const char			*print_aoutsider(const char *format, t_printf *printf);
const char			*init_perc(t_printf *printf, const char *format);
void				check_padding_case_int(t_printf *printf, int res);
void				check_padding_case_adress(t_printf *printf, void *res, \
					char *str);
void				check_padding_case_hex(t_printf *printf, void *ret);
void				check_padding_case(t_printf *printf);
void				ft_output(t_printf *printf, va_list ap);
int					get_next_line(int fd, char **line);
int					check_n(char *stock);
int					ft_printf(const char *format, ...);
int					ft_list_size(t_list *list);
void				ft_list_clear(t_list *begin_list, void (*free_fct)(void *));
void				ft_list_push_front(t_list **begin_list, void *data);
void				ft_list_push_back(t_list **begin_list, void *data);
void				ft_list_foreach(t_list *begin_list, void (*f)(void *));
void				ft_list_remove_if(t_list **begin_list, void *data_ref,
						int (*cmp)(), void (*free_fct)(void *));
t_list				*ft_create_elem(void *data);
t_list				*ft_list_at(t_list *begin_list, unsigned int nbr);
t_list				*ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)());

#endif
