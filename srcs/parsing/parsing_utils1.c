/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 14:30:09 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/08 14:35:09 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	spaces(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s && !s[i])
		return (FAILURE);
	while (!is_whitespace(s[i]))
	{
		count++;
		i++;
	}
	return (count);
}
