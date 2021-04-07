/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 11:52:38 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/06 17:17:10 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	output_int(t_printf *printf, va_list ap)
{
	int	res;

	res = va_arg(ap, int);
	if (printf->orig == 1)
		printf->precision = 0;
	if (res == 0 && printf->precision == 0)
	{
		output_flags(printf);
		return ;
	}
	if (res < 0)
		printf->minus = 1;
	else
		printf->minus = 0;
	printf->len = ft_intlen(res);
	if (printf->minus || printf->plus)
		printf->outputlen += printf->len + 1;
	else
		printf->outputlen += printf->len;
	check_padding_case_int(printf, res);
}

void	output_char(t_printf *printf, va_list ap)
{
	char	res;

	if (printf->perc == 1)
		res = '%';
	else if (printf->perc == 0)
		res = va_arg(ap, int);
	else
		res = 0;
	printf->outputlen += 1;
	printf->len = 1;
	if (printf->padding == 2)
	{
		ft_putchar_fd(res, 1);
		output_flags(printf);
	}
	else
	{
		output_flags(printf);
		ft_putchar_fd(res, 1);
	}
}

char	*negative_adress(int len)
{
	int		i;
	int		diff;
	char	*str;

	i = 2;
	diff = 16 - len;
	if (ft_calloc((void **)&str, (19 - len), sizeof(char)))
		return (NULL);
	str[0] = '0';
	str[1] = 'x';
	while (diff--)
	{
		str[i] = 'f';
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	output_adress(t_printf *printf, va_list ap)
{
	void	*res;
	long	a;
	char	*str;

	a = va_arg(ap, long);
	if (printf->orig == 1)
		printf->precision = 0;
	if (a == 0 && printf->precision == 0)
	{
		check_padding_case_adress(printf, "\0", "0x");
		return ;
	}
	res = ft_int_hexmin(a, "0123456789abcdef");
	if (a < 0)
		str = negative_adress(ft_strlen(res));
	else
		str = "0x";
	printf->len = ft_strlen(res) + ft_strlen(str);
	printf->outputlen += printf->len;
	check_padding_case_adress(printf, res, str);
	free(res);
	if (a < 0)
		free(str);
}

void	ft_output(t_printf *printf, va_list ap)
{
	if (printf->precision == 0 && printf->number == 1)
	{
		check_padding_case(printf);
		return ;
	}
	if (printf->type == 'd' || printf->type == 'i')
		output_int(printf, ap);
	else if (printf->type == 's')
		output_string(printf, ap);
	else if (printf->type == 'u')
		output_uint(printf, ap);
	else if (printf->type == 'c')
		output_char(printf, ap);
	else if (printf->type == 'x')
		output_hexmin(printf, ap);
	else if (printf->type == 'X')
		output_hexmax(printf, ap);
	else if (printf->type == 'p')
		output_adress(printf, ap);
}
