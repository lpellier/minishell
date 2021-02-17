/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnnbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 11:36:44 by lpellier          #+#    #+#             */
/*   Updated: 2020/01/03 16:44:23 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnnbr_fd(int n, int size, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		ft_putnstr_fd("-2147483648", size, fd);
		return ;
	}
	else if (n >= 10 && size != 0)
	{
		ft_putnnbr_fd(n / 10, size, fd);
		ft_putchar_fd(n % 10 + 48, fd);
		size--;
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnnbr_fd(-n, size, fd);
	}
	else
		ft_putchar_fd(n + 48, fd);
}
