/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:39:48 by lpellier          #+#    #+#             */
/*   Updated: 2019/11/25 14:23:57 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*source;

	if (dst != NULL && src != NULL)
	{
		dest = (unsigned char *)dst;
		source = (unsigned char *)src;
		if (dest > source)
		{
			i = len + 1;
			while (--i > 0)
				dest[i - 1] = source[i - 1];
		}
		else
		{
			i = -1;
			while (++i < len)
				dest[i] = source[i];
		}
		return (dst);
	}
	return (ft_strdup("\0"));
}
