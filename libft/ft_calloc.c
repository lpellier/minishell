/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:31:05 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/07 01:07:14 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	a_malloc(void **ptr, int size)
{
	*ptr = malloc(size);
	if (!(*ptr))
		return (1);
	return (0);
}

int	ft_calloc(void **ptr, size_t count, size_t size)
{
	if (count != 0 && size != 0)
	{
		if (a_malloc(ptr, count * size))
			return (1);
		ft_bzero(*ptr, count * size);
		return (0);
	}
	return (1);
}
