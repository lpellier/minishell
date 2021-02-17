/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:16:44 by lpellier          #+#    #+#             */
/*   Updated: 2019/11/18 11:53:41 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s && *s != c)
		s++;
	if (c == '\0' && *s == c)
		return ((char *)s);
	else if (*s == '\0')
		return (NULL);
	else
		return ((char *)s);
}
