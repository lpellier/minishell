/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:10:44 by lpellier          #+#    #+#             */
/*   Updated: 2019/11/25 14:20:50 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	unsigned char	*bottomtext;

	if (b != NULL)
	{
		bottomtext = (unsigned char *)b;
		i = 0;
		while (i < len)
		{
			bottomtext[i] = (unsigned char)c;
			i++;
		}
		return (b);
	}
	return (ft_strdup("\0"));
}
