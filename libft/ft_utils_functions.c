/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:36:54 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/26 12:51:35 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	output_sign(t_printf *printf, int res)
{
	if (printf->minus)
	{
		ft_putchar_fd('-', STDERR_FILENO);
		res *= -1;
	}
	else if (printf->plus)
		ft_putchar_fd('+', STDERR_FILENO);
	else if (printf->space)
	{
		ft_putchar_fd(' ', STDERR_FILENO);
		printf->outputlen += 1;
	}
	return (res);
}

void	put_zeros(t_printf *printf)
{
	int	new;

	if (printf->precision > printf->len)
	{
		new = printf->precision - printf->len;
		while (new--)
		{
			ft_putchar_fd('0', STDERR_FILENO);
			printf->outputlen++;
		}
	}
}

const char	*init_perc(t_printf *printf, const char *format)
{
	printf->type = 'c';
	printf->number = 0;
	printf->perc = 1;
	format += 1;
	return (format);
}

void	output_flags(t_printf *printf)
{
	int	padlength;

	padlength = 0;
	if (printf->number == 1 && printf->precision > printf->width)
		padlength = 0;
	else if (printf->number == 0 && printf->width > printf->len)
		padlength = printf->width - printf->len;
	else if (printf->number == 1 && printf->width > printf->len)
	{
		if (printf->width >= printf->precision && \
			printf->precision > printf->len)
			padlength = printf->width - printf->precision;
		else
			padlength = printf->width - printf->len;
	}
	if ((printf->plus || printf->minus || printf->space) && padlength > 0)
		padlength--;
	printf->outputlen += padlength;
	if (printf->padding == 1 && printf->precision != -1 \
		&& printf->precision < printf->len)
		printf->padding = 3;
	manque_de_place(printf, padlength);
}

void	check_padding_case_hex(t_printf *printf, void *ret)
{
	if (printf->padding == 2)
	{
		put_zeros(printf);
		ft_putnstr_fd(ret, printf->len, STDERR_FILENO);
		output_flags(printf);
	}
	else if (printf->padding == 1)
	{
		output_flags(printf);
		put_zeros(printf);
		ft_putnstr_fd(ret, printf->len, STDERR_FILENO);
	}
	else
	{
		output_flags(printf);
		put_zeros(printf);
		ft_putnstr_fd(ret, printf->len, STDERR_FILENO);
	}
}
