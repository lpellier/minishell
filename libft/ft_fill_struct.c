/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 10:29:31 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/23 12:05:19 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*checkflags(const char *format, t_printf *printf)
{
	while (*format == '-' || *format == '0' || *format == '+')
	{
		if (*format == '+')
		{
			printf->plus += 1;
			while (*format == '+')
				format++;
			format--;
		}
		if (*format == '-' && *(format + 1) == '0')
			printf->padding = 2;
		else if (*format == '0' && *(format + 1) != '-' && *(format - 1) != '-')
			printf->padding = 1;
		else if (*format == '-' && *(format + 1) != '0' && *(format + 1) != '0')
			printf->padding = 2;
		format++;
	}
	return (format);
}

const char	*checkwidth(const char *format, t_printf *printf, va_list ap)
{
	if (*format >= '0' && *format <= '9')
	{
		while (*format >= '0' && *format <= '9')
		{
			printf->width = printf->width * 10 + *format - 48;
			format++;
		}
	}
	else if (*format == '*')
	{
		printf->width = va_arg(ap, int);
		if (printf->width < 0)
		{
			printf->width *= -1;
			printf->padding = 2;
		}
		format++;
	}
	return (format);
}

const char	*checkprecision(const char *format, t_printf *printf, va_list ap)
{
	if (*format == '.')
	{
		printf->precision = 0;
		format++;
		if (*format >= '0' && *format <= '9')
		{
			while (*format >= '0' && *format <= '9')
			{
				printf->precision = printf->precision * 10 + *format - 48;
				format++;
			}
		}
		else if (*format == '*')
		{
			printf->precision = va_arg(ap, int);
			format++;
		}
		if (printf->precision < 0 && printf->precision != -1)
			printf->precision = -1;
	}
	return (format);
}

const char	*checktype(const char *format, t_printf *printf)
{
	if (*format == '%')
	{
		format = init_perc(printf, format);
		return (format);
	}
	if (*format == 'p' || *format == 'd' || *format == 'i'
	|| *format == 'u' || *format == 'x' || *format == 'X')
	{
		printf->type = *format;
		printf->number = 1;
		format++;
	}
	else if (*format == 'c' || *format == 's')
	{
		printf->type = *format;
		printf->number = 0;
		format++;
	}
	if (printf->precision == 0 && printf->number == 1)
	{
		printf->precision = -1;
		printf->orig = 1;
	}
	return (format);
}

const char	*ft_fill_struct(const char *format, t_printf *printf, va_list ap)
{
	if (*format == '+')
	{
		printf->plus += 1;
		while (*format == '+')
			format++;
	}
	if (*format == ' ')
	{
		printf->space += 1;
		while (*format == ' ')
			format++;
	}
	format = checkflags(format, printf);
	format = checkwidth(format, printf, ap);
	format = checkprecision(format, printf, ap);
	format = checktype(format, printf);
	return (format);
}
