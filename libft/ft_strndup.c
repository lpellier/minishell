/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:18:40 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/25 13:25:53 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strndup(const char *s1, int size)
{
	char	*res;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s1) < size ? ft_strlen(s1) : size;
	if (s1 != NULL)
	{
		if (!(res = ft_calloc(len + 1, sizeof(const char))))
			return (NULL);
		while (s1[i] && i < len)
		{
			res[i] = s1[i];
			i++;
		}
		res[i] = '\0';
		return (res);
	}
	return (NULL);
}
