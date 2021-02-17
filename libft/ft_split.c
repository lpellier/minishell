/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:44:59 by lpellier          #+#    #+#             */
/*   Updated: 2019/11/14 12:05:33 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		get_n_word(const char *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	while (s[j])
	{
		if ((s[j] == c && s[j - 1] != c && c && s[j + 1])
		|| (s[j] != c && s[j + 1] == '\0'))
			i++;
		j++;
	}
	return (i);
}

char		*extract_word(const char *s, char c)
{
	int		end;

	end = 0;
	while (s[end] && s[end] != c)
		end++;
	return (ft_substr(s, 0, end));
}

char		**ft_split(const char *s, char c)
{
	char	**str;
	size_t	n_word;
	size_t	j;

	if (s == NULL)
		return (NULL);
	j = 0;
	n_word = get_n_word(s, c);
	if (!(str = ft_calloc(n_word + 1, sizeof(char *))))
		return (NULL);
	while (j < n_word && *s)
	{
		while (*s == c)
			s++;
		str[j] = extract_word(s, c);
		s = ft_strchr(s, c);
		j++;
	}
	str[j] = NULL;
	return (str);
}
