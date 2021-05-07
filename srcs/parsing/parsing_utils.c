/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:24:33 by lpellier          #+#    #+#             */
/*   Updated: 2021/05/07 15:23:19 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	multiple_args(char *str)
{
	char	**split;
	int		i;

	split = ft_split(str, 32);
	if (!split)
		return (SUCCESS);
	i = 0;
	while (split[i])
		i++;
	if (i > 1)
		return (FAILURE);
	return (SUCCESS);
}

int	ft_isalpha_ordollar(int c)
{
	if (c == '?' || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}
