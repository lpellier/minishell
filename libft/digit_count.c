/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 15:39:01 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/06 10:52:09 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	digit_count(long value, int base)
{
	size_t	i;

	i = 0;
	if (value < 0)
		value = -value;
	while (value)
	{
		value /= base;
		i++;
	}
	return (i);
}
