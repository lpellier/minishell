/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaspellier <lucaspellier@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 10:29:31 by lpellier          #+#    #+#             */
/*   Updated: 2020/03/25 19:58:16 by lucaspellie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*checkflags(const char *format, t_printf *info)
{
	while (*format == '-' || *format == '0' || *format == '+')
	{
		if (*format == '+')
		{
			info->plus += 1;
			while (*format == '+')
				format++;
			format--;
		}
		if (*format == '-' && *(format + 1) == '0')
			info->padding = 2;
		else if (*format == '0' && *(format + 1) != '-' && *(format - 1) != '-')
			info->padding = 1;
		else if (*format == '-' && *(format + 1) != '0' && *(format + 1) != '0')
			info->padding = 2;
		format++;
	}
	return (format);
}

const char	*checkwidth(const char *format, t_printf *info, va_list ap)
{
	if (*format >= '0' && *format <= '9')
	{
		while (*format >= '0' && *format <= '9')
		{
			info->width = info->width * 10 + *format - 48;
			format++;
		}
	}
	else if (*format == '*')
	{
		info->width = va_arg(ap, int);
		if (info->width < 0)
		{
			info->width *= -1;
			info->padding = 2;
		}
		format++;
	}
	return (format);
}

const char	*checkprecision(const char *format, t_printf *info, va_list ap)
{
	if (*format == '.')
	{
		info->precision = 0;
		format++;
		if (*format >= '0' && *format <= '9')
		{
			while (*format >= '0' && *format <= '9')
			{
				info->precision = info->precision * 10 + *format - 48;
				format++;
			}
		}
		else if (*format == '*')
		{
			info->precision = va_arg(ap, int);
			format++;
		}
		if (info->precision < 0 && info->precision != -1)
			info->precision = -1;
	}
	return (format);
}

const char	*checktype(const char *format, t_printf *info)
{
	if (*format == '%')
	{
		format = init_perc(info, format);
		return (format);
	}
	if (*format == 'p' || *format == 'd' || *format == 'i'
	|| *format == 'u' || *format == 'x' || *format == 'X')
	{
		info->type = *format;
		info->number = 1;
		format++;
	}
	else if (*format == 'c' || *format == 's')
	{
		info->type = *format;
		info->number = 0;
		format++;
	}
	if (info->precision == 0 && info->number == 1)
	{
		info->precision = -1;
		info->orig = 1;
	}
	return (format);
}

const char	*ft_fill_struct(const char *format, t_printf *info, va_list ap)
{
	if (*format == '+')
	{
		info->plus += 1;
		while (*format == '+')
			format++;
	}
	if (*format == ' ')
	{
		info->space += 1;
		while (*format == ' ')
			format++;
	}
	format = checkflags(format, info);
	format = checkwidth(format, info, ap);
	format = checkprecision(format, info, ap);
	format = checktype(format, info);
	return (format);
}
