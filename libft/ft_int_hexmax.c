/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_hexmax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:32:27 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/06 16:13:45 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_int_hexmax(long n, char *tab)
{
	char			*res;
	int				taille;
	int				i;

	if (n < 0)
		return (ft_int_hexmax((-n - 1), "FEDCBA9876543210"));
	else if (n > 0)
	{
		i = 0;
		taille = digit_count(n, 16);
		if (ft_calloc((void **)&res, taille + 1, (sizeof(char))))
			return (NULL);
		taille--;
		while (n)
		{
			res[taille - i++] = tab[n % 16];
			n /= 16;
		}
		res[taille + 1] = '\0';
		return (res);
	}
	return (ft_strdup("0"));
}
