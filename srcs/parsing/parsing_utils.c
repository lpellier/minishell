/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:24:33 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/27 17:13:56 by lpellier         ###   ########.fr       */
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
