/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_other.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaspellier <lucaspellier@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:34:26 by lpellier          #+#    #+#             */
/*   Updated: 2020/03/25 19:53:35 by lucaspellie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	output_string(t_printf *info, va_list ap)
{
	char	*res;

	res = (char *)va_arg(ap, char *);
	if (res == NULL)
		res = "(null)";
	info->len = (int)ft_strlen(res);
	info->len = (info->precision < info->len && info->precision != -1 ? \
	info->precision : info->len);
	info->outputlen += info->len;
	if (info->padding == 2)
	{
		ft_putnstr_fd(res, info->len, 1);
		output_flags(info);
	}
	else
	{
		output_flags(info);
		ft_putnstr_fd(res, info->len, 1);
	}
}

void	output_uint(t_printf *info, va_list ap)
{
	unsigned int	res;

	res = va_arg(ap, unsigned int);
	if (info->orig == 1)
		info->precision = 0;
	if (res == 0 && info->precision == 0)
	{
		output_flags(info);
		return ;
	}
	info->len = ft_uintlen(res);
	info->outputlen += (info->plus ? info->len + 1 : info->len);
	if (info->padding == 2)
	{
		put_zeros(info);
		ft_putunbr_fd(res, 1);
		output_flags(info);
	}
	else
	{
		output_flags(info);
		put_zeros(info);
		ft_putunbr_fd(res, 1);
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
	if (!(str = malloc(sizeof(char) * (8 - diff))))
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

void	output_hexmin(t_printf *info, va_list ap)
{
	char	*res;
	long	a;

	a = va_arg(ap, int);
	if (info->orig == 1)
		info->precision = 0;
	if (a == 0 && info->precision == 0)
	{
		output_flags(info);
		return ;
	}
	res = ft_int_hexmin(a, "0123456789abcdef");
	if (a < 0)
		res = fill_f(res, 0);
	info->len = ft_strlen(res);
	info->outputlen += info->len;
	check_padding_case_hex(info, res);
	free(res);
}

void	output_hexmax(t_printf *info, va_list ap)
{
	char	*res;
	long	a;

	a = va_arg(ap, int);
	if (info->orig == 1)
		info->precision = 0;
	if (a == 0 && info->precision == 0)
	{
		output_flags(info);
		return ;
	}
	res = ft_int_hexmax(a, "0123456789ABCDEF");
	if (a < 0)
		res = fill_f(res, 10);
	info->len = ft_strlen(res);
	info->outputlen += info->len;
	check_padding_case_hex(info, res);
	free(res);
}
