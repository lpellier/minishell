/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 10:48:12 by lpellier          #+#    #+#             */
/*   Updated: 2021/05/07 15:43:48 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	assign_nbrs(int nbr, long *n, size_t *len)
{
	*n = nbr;
	*len = 0;
	if (*n < 0)
		*len = 1;
	if (*n < 0)
		*n *= -1;
	if (!nbr)
		(*len)++;
	while (nbr)
	{
		(*len)++;
		if (*len)
			nbr /= 10;
	}
}

char	*ft_itoa(int nbr)
{
	long	n;
	size_t	len;
	char	*str;

	assign_nbrs(nbr, &n, &len);
	if (ft_calloc((void **)&str, len + 1, sizeof(str)))
		return (NULL);
	*(str + len--) = '\0';
	while (n > 0)
	{
		*(str + len--) = n % 10 + '0';
		n /= 10;
	}
	if (len == 0 && str[1] == '\0')
		*(str + len) = '0';
	if (len == 0 && str[1] != '\0')
		*(str + len) = '-';
	return (str);
}
