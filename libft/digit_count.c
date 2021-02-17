/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 15:39:01 by lpellier          #+#    #+#             */
/*   Updated: 2020/01/03 16:44:03 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		digit_count(long value, int base)
{
	size_t i;

	i = 0;
	value = (value < 0 ? -value : value);
	while (value)
	{
		value /= base;
		i++;
	}
	return (i);
}
