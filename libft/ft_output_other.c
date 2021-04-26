/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_other.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:34:26 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/26 10:38:23 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	output_string(t_printf *printf, va_list ap)
{
	char	*res;

	res = (char *)va_arg(ap, char *);
	if (res == NULL)
		res = "(null)";
	printf->len = (int)ft_strlen(res);
	if (printf->precision < printf->len && printf->precision != -1)
		printf->len = printf->precision;
	else
		printf->len = printf->len;
	printf->outputlen += printf->len;
	if (printf->padding == 2)
	{
		ft_putnstr_fd(res, printf->len, STDERR_FILENO);
		output_flags(printf);
	}
	else
	{
		output_flags(printf);
		ft_putnstr_fd(res, printf->len, STDERR_FILENO);
	}
}

void	output_uint(t_printf *printf, va_list ap)
{
	unsigned int	res;

	res = va_arg(ap, unsigned int);
	if (printf->orig == 1)
		printf->precision = 0;
	if (res == 0 && printf->precision == 0)
	{
		output_flags(printf);
		return ;
	}
	printf->len = ft_uintlen(res);
	if (printf->plus)
		printf->outputlen += printf->len + 1;
	else
		printf->outputlen += printf->len;
	if (printf->padding == 2)
		reduce_me(printf, res);
	else
	{
		output_flags(printf);
		put_zeros(printf);
		ft_putunbr_fd(res, STDERR_FILENO);
	}
}

char	*fill_f(char *res, int size)
{
	int		i;
	int		diff;
	char	*str;
	char	*ret;

	i = 0;
	diff = 8 - ft_strlen(res);
	if (ft_calloc((void **)&str, (8 - diff), sizeof(char)))
		return (NULL);
	while (diff--)
	{
		if (size == 10)
			str[i] = 'F';
		else
			str[i] = 'f';
		i++;
	}
	str[i] = '\0';
	ret = ft_strjoin(str, res);
	free(str);
	return (ret);
}

void	output_hexmin(t_printf *printf, va_list ap)
{
	char	*res;
	long	a;

	a = va_arg(ap, int);
	if (printf->orig == 1)
		printf->precision = 0;
	if (a == 0 && printf->precision == 0)
	{
		output_flags(printf);
		return ;
	}
	res = ft_int_hexmin(a, "0123456789abcdef");
	if (a < 0)
		res = fill_f(res, 0);
	printf->len = ft_strlen(res);
	printf->outputlen += printf->len;
	check_padding_case_hex(printf, res);
	free(res);
}

void	output_hexmax(t_printf *printf, va_list ap)
{
	char	*res;
	long	a;

	a = va_arg(ap, int);
	if (printf->orig == 1)
		printf->precision = 0;
	if (a == 0 && printf->precision == 0)
	{
		output_flags(printf);
		return ;
	}
	res = ft_int_hexmax(a, "0123456789ABCDEF");
	if (a < 0)
		res = fill_f(res, 10);
	printf->len = ft_strlen(res);
	printf->outputlen += printf->len;
	check_padding_case_hex(printf, res);
	free(res);
}
