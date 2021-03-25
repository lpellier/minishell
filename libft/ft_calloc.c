/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:31:05 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/25 14:08:11 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (count != 0 && size != 0)
	{
		if (!(mem = malloc(count * size)))
			return (NULL);
		ft_bzero(mem, count * size);
		return (mem);
	}
	return (malloc(1));
}
