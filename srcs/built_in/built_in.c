/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:05:33 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/19 14:20:24 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			str_isalpha_withplus(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '+')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

char	last_char(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
		i++;
	if (i > 0)
		c = str[i - 1];
	else
		c = '\0';
	return(c);
}
