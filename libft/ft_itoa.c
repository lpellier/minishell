/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:09:54 by lpellier          #+#    #+#             */
/*   Updated: 2019/11/16 14:40:14 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countchar(int n)
{
	int	i;

	i = 1;
	if (n < 0)
		n *= -1;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_int_str(char *str, int n, int len)
{
	int		start;

	str[len] = '\0';
	len -= 1;
	if (n < 0)
	{
		n *= -1;
		start = 1;
		str[0] = '-';
	}
	else
		start = 0;
	while (len >= start)
	{
		str[len] = n % 10 + 48;
		n /= 10;
		len--;
	}
	return (str);
}

char	*ft_strnew(size_t size)
{
	char	*new;
	size_t	i;

	i = 0;
	if (!(new = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	while (i < size)
	{
		new[i] = '\0';
		i++;
	}
	new[i] = '\0';
	return (new);
}

int		ft_blacksheep(int n, void *str)
{
	char	*ptsr;
	int		x;
	char	*ftsr;

	ptsr = (char *)str;
	if (n == -2147483648)
	{
		x = 0;
		ftsr = "-2147483648";
		while (x <= 12)
		{
			ptsr[x] = ftsr[x];
			x++;
		}
		return (1);
	}
	else if (n == 0)
	{
		ptsr[0] = '0';
		ptsr[1] = '\0';
		return (1);
	}
	return (0);
}

char	*ft_itoa(int n)
{
	char			*str;
	long long int	len;

	len = ft_countchar(n);
	if (n < 0)
		len += 1;
	str = ft_strnew(len);
	if (ft_blacksheep(n, str))
		return (str);
	if (!str)
		return (NULL);
	str = ft_int_str(str, n, len);
	return (str);
}
