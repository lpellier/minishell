/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:18:40 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/06 17:06:57 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int size)
{
	char	*res;
	int		i;
	int		len;

	i = 0;
	if (ft_strlen(s1) < size)
		len = ft_strlen(s1);
	else
		len = size;
	if (s1 != NULL)
	{
		if (ft_calloc((void **)&res, len + 1, sizeof(const char)))
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
