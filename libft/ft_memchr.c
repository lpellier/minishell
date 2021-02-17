/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:11:37 by lpellier          #+#    #+#             */
/*   Updated: 2019/11/25 14:29:22 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	char		*res;

	if (s != NULL)
	{
		i = 0;
		res = (void *)s;
		while (i < n)
		{
			if (res[i] == (char)c)
				return (&res[i]);
			i++;
		}
	}
	return (NULL);
}
