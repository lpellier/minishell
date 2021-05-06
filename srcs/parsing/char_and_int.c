/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_and_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 17:42:12 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/05 17:42:45 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	intcat(int *dest, int start, int *src)
{
	int		i;

	i = 0;
	while (src[i] != -1)
	{
		dest[start] = src[i];
		i++;
		start++;
	}
}

void	add_int(int *dest, int key, int index)
{
	int		*tmp;

	tmp = sublint(dest, index);
	dest[index] = key;
	index++;
	intcat(dest, index, tmp);
	secure_free(tmp);
}

void	add_char(char *dest, char key, int index)
{
	char	*tmp_one;
	char	*tmp_two;

	tmp_one = ft_substr(dest, 0, index);
	tmp_two = ft_substr(dest, index, ft_strlen(dest));
	ft_bzero(dest, ft_strlen(dest));
	ft_strcpy(dest, tmp_one);
	ft_strncat(dest, &key, 1);
	ft_strncat(dest, tmp_two, ft_strlen(tmp_two));
	secure_free(tmp_one);
	secure_free(tmp_two);
}

void	remove_int(int	*lint, int index)
{
	while (lint[index] != -1)
	{
		lint[index] = lint[index + 1];
		index++;
	}
}

void	remove_char(char *line, int index)
{
	while (line[index])
	{
		line[index] = line[index + 1];
		index++;
	}
}
