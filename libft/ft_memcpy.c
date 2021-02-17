/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:04:32 by lpellier          #+#    #+#             */
/*   Updated: 2019/11/25 14:26:54 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dest;
	const char	*source;

	if (dst != NULL && src != NULL)
	{
		i = 0;
		source = src;
		dest = dst;
		while (n)
		{
			dest[i] = source[i];
			i++;
			n--;
		}
		return (dst);
	}
	return (ft_strdup("\0"));
}
