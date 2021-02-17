/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:38:40 by lpellier          #+#    #+#             */
/*   Updated: 2019/11/25 14:26:31 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			len;
	char		*test;

	if (s != NULL)
	{
		len = ft_strlen(s);
		test = (char *)s + len;
		while (*test != c)
		{
			if (test == s)
				return (NULL);
			test--;
		}
		return (test);
	}
	return (ft_strdup("\0"));
}
