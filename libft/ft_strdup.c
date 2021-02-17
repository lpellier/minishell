/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:44:43 by lpellier          #+#    #+#             */
/*   Updated: 2019/11/25 14:24:33 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		i;

	i = 0;
	if (s1 != NULL)
	{
		if (!(res = malloc(sizeof(const char) * ft_strlen(s1) + 1)))
			return (NULL);
		while (s1[i])
		{
			res[i] = s1[i];
			i++;
		}
		res[i] = '\0';
		return (res);
	}
	return (NULL);
}
