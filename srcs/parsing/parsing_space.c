/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:36:52 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/20 13:12:07 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (SUCCESS);
	return (FAILURE);
}

int	spaces(char *s, int index)
{
	int	i;
	int	block_end;
	int	count;

	i = 0;
	count = 0;
	block_end = check_if_block(index);
	if (!s || !s[i] || block_end >= 0)
		return (0);
	while (s[i] && !is_whitespace(s[i]) && block_end == -1)
	{
		count++;
		i++;
		block_end = check_if_block(index + i);
	}
	return (count);
}
