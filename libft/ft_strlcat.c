/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:12:18 by lpellier          #+#    #+#             */
/*   Updated: 2019/11/25 13:45:26 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t size_src;
	size_t size_dest;
	size_t i;

	if (dst != NULL && src != NULL)
	{
		size_src = ft_strlen(src);
		size_dest = ft_strlen((const char *)dst);
		i = 0;
		if ((dstsize < size_dest))
			return (dstsize + size_src);
		while (src[i] && size_dest + i < dstsize - 1)
		{
			dst[size_dest + i] = src[i];
			i++;
		}
		dst[size_dest + i] = '\0';
		return (size_dest + size_src);
	}
	return (0);
}
