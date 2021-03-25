/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:42:47 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/25 14:08:27 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*buffer;
	size_t			i;

	if (s != NULL)
	{
		i = 0;
		buffer = (unsigned char*)s;
		while (i < n)
		{
			buffer[i] = 0;
			i++;
		}
	}
}
