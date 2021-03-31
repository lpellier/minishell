/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_auxiliary_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:28:16 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/23 12:05:16 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*print_before(const char *format, t_printf *printf)
{
	while (*format != '%' && *format != '\0')
	{
		ft_putchar_fd(*format, 1);
		printf->outputlen++;
		format++;
	}
	if (*(format + 1) != '\0')
		return (format + 1);
	else
		return (NULL);
}

const char	*print_aoutsider(const char *format, t_printf *printf)
{
	while (*format != '%' && *format)
	{
		ft_putchar_fd(*format, 1);
		printf->outputlen += 1;
		format++;
	}
	if (*format != '\0')
		format++;
	return (format);
}

void		check_padding_case_int(t_printf *printf, int res)
{
	if (printf->padding == 2)
	{
		res = output_sign(printf, res);
		put_zeros(printf);
		ft_putnbr_fd(res, 1);
		output_flags(printf);
	}
	else if (printf->padding == 1)
	{
		res = (printf->precision == -1 ? output_sign(printf, res) : res);
		output_flags(printf);
		res = (printf->precision != -1 ? output_sign(printf, res) : res);
		put_zeros(printf);
		ft_putnbr_fd(res, 1);
	}
	else
	{
		output_flags(printf);
		res = output_sign(printf, res);
		put_zeros(printf);
		ft_putnbr_fd(res, 1);
	}
}

void		check_padding_case_adress(t_printf *printf, void *res, char *str)
{
	if (printf->padding == 2)
	{
		put_zeros(printf);
		ft_putstr_fd(str, 1);
		ft_putnstr_fd(res, printf->len, 1);
		output_flags(printf);
	}
	else
	{
		output_flags(printf);
		put_zeros(printf);
		ft_putstr_fd(str, 1);
		ft_putnstr_fd(res, printf->len, 1);
	}
}

void		check_padding_case(t_printf *printf)
{
	if (printf->padding == 2)
	{
		output_sign(printf, 0);
		output_flags(printf);
	}
	else
	{
		output_flags(printf);
		output_sign(printf, 0);
	}
}
