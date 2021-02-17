/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:18:09 by lpellier          #+#    #+#             */
/*   Updated: 2019/11/18 12:04:15 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long long			res;
	int					sign;
	int					max_sign;

	if (str == NULL)
		return (0);
	res = 0;
	sign = 0;
	max_sign = 0;
	while (*str && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	while (*str == '-' || *str == '+')
	{
		sign += (*str == '-' ? 1 : 0);
		max_sign++;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - 48;
		str++;
	}
	if (max_sign > 1)
		return (0);
	return (sign == 1 ? -res : res);
}
