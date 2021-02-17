/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_auxiliary_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaspellier <lucaspellier@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:28:16 by lpellier          #+#    #+#             */
/*   Updated: 2020/03/25 19:52:53 by lucaspellie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*print_before(const char *format, t_printf *info)
{
	while (*format != '%' && *format != '\0')
	{
		ft_putchar_fd(*format, 1);
		info->outputlen++;
		format++;
	}
	if (*(format + 1) != '\0')
		return (format + 1);
	else
		return (NULL);
}

const char	*print_aoutsider(const char *format, t_printf *info)
{
	while (*format != '%' && *format)
	{
		ft_putchar_fd(*format, 1);
		info->outputlen += 1;
		format++;
	}
	if (*format != '\0')
		format++;
	return (format);
}

void		check_padding_case_int(t_printf *info, int res)
{
	if (info->padding == 2)
	{
		res = output_sign(info, res);
		put_zeros(info);
		ft_putnbr_fd(res, 1);
		output_flags(info);
	}
	else if (info->padding == 1)
	{
		res = (info->precision == -1 ? output_sign(info, res) : res);
		output_flags(info);
		res = (info->precision != -1 ? output_sign(info, res) : res);
		put_zeros(info);
		ft_putnbr_fd(res, 1);
	}
	else
	{
		output_flags(info);
		res = output_sign(info, res);
		put_zeros(info);
		ft_putnbr_fd(res, 1);
	}
}

void		check_padding_case_adress(t_printf *info, void *res, char *str)
{
	if (info->padding == 2)
	{
		put_zeros(info);
		ft_putstr_fd(str, 1);
		ft_putnstr_fd(res, info->len, 1);
		output_flags(info);
	}
	else
	{
		output_flags(info);
		put_zeros(info);
		ft_putstr_fd(str, 1);
		ft_putnstr_fd(res, info->len, 1);
	}
}

void		check_padding_case(t_printf *info)
{
	if (info->padding == 2)
	{
		output_sign(info, 0);
		output_flags(info);
	}
	else
	{
		output_flags(info);
		output_sign(info, 0);
	}
}
