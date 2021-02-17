/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:07:35 by lpellier          #+#    #+#             */
/*   Updated: 2019/11/25 14:25:46 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_check_needle(const char *str, const char *to_find)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[j] == to_find[i] && str[j] != '\0')
	{
		i++;
		j++;
	}
	if (to_find[i] == '\0')
		return (1);
	else
		return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (haystack != NULL && needle != NULL)
	{
		if (haystack == needle)
			return ((char*)haystack);
		if (needle[j] == '\0')
			return ((char*)haystack);
		while (haystack[i] != '\0' && (i + ft_strlen(needle) < (int)len))
		{
			if (haystack[i] == needle[j])
			{
				if (ft_check_needle(&haystack[i], needle) == 1)
					return (&((char*)haystack)[i]);
			}
			i++;
		}
	}
	return (NULL);
}
