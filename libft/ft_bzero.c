/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:42:47 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/26 12:47:43 by lpellier         ###   ########.fr       */
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
		buffer = (unsigned char *)s;
		while (i < n)
		{
			buffer[i] = 0;
			i++;
		}
	}
}
