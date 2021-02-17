/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:36:01 by lpellier          #+#    #+#             */
/*   Updated: 2019/11/25 14:22:47 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s_one;
	const unsigned char	*s_two;

	if (s1 != NULL && s2 != NULL)
	{
		if (s1 == s2 || n == 0)
			return (0);
		s_one = (const unsigned char *)s1;
		s_two = (const unsigned char *)s2;
		while (n--)
		{
			if (*s_one != *s_two)
				return (*s_one - *s_two);
			if (n)
			{
				s_one++;
				s_two++;
			}
		}
	}
	return (0);
}
