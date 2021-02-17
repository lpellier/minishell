/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaspellier <lucaspellier@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 10:49:54 by lpellier          #+#    #+#             */
/*   Updated: 2020/03/25 21:09:58 by lucaspellie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check_n(char *stock)
{
	int		i;

	i = 0;
	if (stock == NULL)
		return (0);
	while (*stock)
	{
		if (*stock == '\n')
			return (i + 1);
		stock++;
		i++;
	}
	return (0);
}
