/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:44:59 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/07 17:38:03 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_len(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static	void	ft_strstr_copy(char **dest, char **src1, char *src2)
{
	int		i;

	i = 0;
	while (src1[i])
	{
		dest[i] = src1[i];
		i++;
	}
	dest[i] = src2;
	dest[i + 1] = NULL;
}

static	char	**ft_strstr_push(char **old, char *new)
{
	char	**ret;
	int		i;

	i = 0;
	if (old)
	{
		if (ft_calloc((void **)&ret, ft_len(old) + 2, sizeof(char *)))
			return (NULL);
		ft_strstr_copy(ret, old, new);
		free(old);
		return (ret);
	}
	if (ft_calloc((void **)&ret, 2, sizeof(char *)))
		return (NULL);
	ret[0] = new;
	ret[1] = NULL;
	return (ret);
}

char	**ft_split(const char *s, char c)
{
	static char	**buffer;
	char		**ret;
	char		*tmp;
	int			i;

	i = 0;
	if (!s)
		return (NULL);
	if (s && *s == c)
		return (ft_split(++s, c));
	if (s && *s)
	{
		while (s[i] && s[i] != c)
			i++;
		tmp = ft_substr(s, 0, i);
		buffer = ft_strstr_push(buffer, tmp);
		return (ft_split(&s[i], c));
	}
	ret = buffer;
	buffer = NULL;
	return (ret);
}
