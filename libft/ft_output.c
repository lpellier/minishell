/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaspellier <lucaspellier@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 11:52:38 by lpellier          #+#    #+#             */
/*   Updated: 2020/03/25 19:53:31 by lucaspellie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	output_int(t_printf *info, va_list ap)
{
	int		res;

	res = va_arg(ap, int);
	if (info->orig == 1)
		info->precision = 0;
	if (res == 0 && info->precision == 0)
	{
		output_flags(info);
		return ;
	}
	info->minus = (res < 0 ? 1 : 0);
	info->len = ft_intlen(res);
	info->outputlen += ((info->minus || info->plus) ? \
	info->len + 1 : info->len);
	check_padding_case_int(info, res);
}

void	output_char(t_printf *info, va_list ap)
{
	char	res;

	if (info->perc == 1)
		res = '%';
	else if (info->perc == 0)
		res = va_arg(ap, int);
	info->outputlen += 1;
	info->len = 1;
	if (info->padding == 2)
	{
		ft_putchar_fd(res, 1);
		output_flags(info);
	}
	else
	{
		output_flags(info);
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
	if (!(str = malloc(sizeof(char) * (19 - len))))
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

void	output_adress(t_printf *info, va_list ap)
{
	void				*res;
	long				a;
	char				*str;

	a = va_arg(ap, long);
	if (info->orig == 1)
		info->precision = 0;
	if (a == 0 && info->precision == 0)
	{
		check_padding_case_adress(info, "\0", "0x");
		return ;
	}
	res = ft_int_hexmin(a, "0123456789abcdef");
	if (a < 0)
		str = negative_adress(ft_strlen(res));
	else
		str = "0x";
	info->len = ft_strlen(res) + ft_strlen(str);
	info->outputlen += info->len;
	check_padding_case_adress(info, res, str);
	free(res);
	if (a < 0)
		free(str);
}

void	ft_output(t_printf *info, va_list ap)
{
	if (info->precision == 0 && info->number == 1)
	{
		check_padding_case(info);
		return ;
	}
	if (info->type == 'd' || info->type == 'i')
		output_int(info, ap);
	else if (info->type == 's')
		output_string(info, ap);
	else if (info->type == 'u')
		output_uint(info, ap);
	else if (info->type == 'c')
		output_char(info, ap);
	else if (info->type == 'x')
		output_hexmin(info, ap);
	else if (info->type == 'X')
		output_hexmax(info, ap);
	else if (info->type == 'p')
		output_adress(info, ap);
}
