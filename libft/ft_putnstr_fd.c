/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 11:38:37 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/03 20:23:00 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnstr_fd(char *s, int size, int fd)
{
	int	i;

	if (s == NULL || size == 0)
		return ;
	i = 0;
	while (s[i] && size != 0)
	{
		ft_putchar_fd(s[i], fd);
		i++;
		size--;
	}
}
