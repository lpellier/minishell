/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:50:14 by lpellier          #+#    #+#             */
/*   Updated: 2019/11/12 16:26:18 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_checkset(char c, char const *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		ft_checkend(char const *s1, char const *set)
{
	int end;

	end = ft_strlen(s1) - 1;
	while (ft_checkset(s1[end], set))
		end--;
	return (end + 1);
}

int		ft_len(char const *s1, char const *set)
{
	int		count;
	int		i;
	int		start;
	int		end;

	end = ft_checkend(s1, set);
	start = 0;
	i = 0;
	count = 0;
	while (s1[start] && ft_checkset(s1[start], set))
		start++;
	while (s1[i])
	{
		if (ft_checkset(s1[i], set) && (i < start || i > end))
			count++;
		i++;
	}
	return (i - count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		start;
	int		i;
	int		end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	end = ft_checkend(s1, set);
	i = 0;
	start = 0;
	if (!(res = malloc(sizeof(char) * ft_len(s1, set))))
		return (NULL);
	while (ft_checkset(s1[start], set))
		start++;
	while (start < end)
	{
		res[i] = s1[start];
		start++;
		i++;
	}
	res[i] = '\0';
	return (res);
}
