/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 10:49:54 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/08 22:53:09 by lpellier         ###   ########.fr       */
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
