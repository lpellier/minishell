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

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
size_t		i;
size_t		j;
	i = 0;
if (*needle == '\0' || needle == NULL)
return ((char*)haystack);
while (haystack[i] != '\0' && i < len)
	{
		j = 0;
while (needle[j] == haystack[i + j] && i + j < len)
		{
if (needle[j + 1] == '\0')
			{
return ((char*)haystack + i);
			}
			j++;
		}
		i++;
	}
return (NULL);
}
