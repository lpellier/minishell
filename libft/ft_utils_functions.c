/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaspellier <lucaspellier@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:36:54 by lpellier          #+#    #+#             */
/*   Updated: 2020/03/25 19:56:14 by lucaspellie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			output_sign(t_printf *info, int res)
{
	if (info->minus)
	{
		ft_putchar_fd('-', 1);
		res *= -1;
	}
	else if (info->plus)
		ft_putchar_fd('+', 1);
	else if (info->space)
	{
		ft_putchar_fd(' ', 1);
		info->outputlen += 1;
	}
	return (res);
}

void		put_zeros(t_printf *info)
{
	int		new;

	if (info->precision > info->len)
	{
		new = info->precision - info->len;
		while (new--)
		{
			ft_putchar_fd('0', 1);
			info->outputlen++;
		}
	}
}

const char	*init_perc(t_printf *info, const char *format)
{
	info->type = 'c';
	info->number = 0;
	info->perc = 1;
	format += 1;
	return (format);
}

void		output_flags(t_printf *info)
{
	int		padlength;

	padlength = 0;
	if (info->number == 1 && info->precision > info->width)
		padlength = 0;
	else if (info->number == 0 && info->width > info->len)
		padlength = info->width - info->len;
	else if (info->number == 1 && info->width > info->len)
		padlength = (info->width >= info->precision && \
		info->precision > info->len ? \
		info->width - info->precision : info->width - info->len);
	if ((info->plus || info->minus || info->space) && padlength > 0)
		padlength--;
	info->outputlen += padlength;
	if (info->padding == 1 && info->precision != -1 \
		&& info->precision < info->len)
		info->padding = 3;
	if (info->padding != 1 || (info->number == 1 && info->precision != -1))
		while (padlength--)
			ft_putchar_fd(' ', 1);
	else
		while (padlength--)
			ft_putchar_fd('0', 1);
}

void		check_padding_case_hex(t_printf *info, void *ret)
{
	if (info->padding == 2)
	{
		put_zeros(info);
		ft_putnstr_fd(ret, info->len, 1);
		output_flags(info);
	}
	else if (info->padding == 1)
	{
		output_flags(info);
		put_zeros(info);
		ft_putnstr_fd(ret, info->len, 1);
	}
	else
	{
		output_flags(info);
		put_zeros(info);
		ft_putnstr_fd(ret, info->len, 1);
	}
}
