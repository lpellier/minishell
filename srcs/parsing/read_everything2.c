/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_everything2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:24:22 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/08 16:25:31 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	backslash(char *line, int *index, int dquote)
{
	if (!dquote)
	{
		remove_char(line, *index);
		*index += 1;
	}
	else if (dquote)
	{
		if (line[*index + 1] && (line[*index + 1] == BSLASH || line[*index + 1] == \
			'$' || line[*index + 1] == DQUOTE))
		{
			remove_char(line, *index);
			if (!line[*index + 1])
				return (FAILURE);
		}
		*index += 1;
	}
	return (SUCCESS);
}

int	count_exceptions(int quote, int dquote)
{
	if (quote % 2 != 0 || dquote % 2 != 0)
		return (1);
	else
		return (0);
}

int	quote(char *line, int *index)
{
	remove_char(line, *index);
	ft_list_push_front(&g_info.block_head, create_block_struct(*index, -1));
	while (line[*index] && line[*index] != QUOTE)
		*index += 1;
	if (!line[*index])
		return (1);
	else if (line[*index] == QUOTE)
	{
		remove_char(line, *index);
		((t_block *)g_info.block_head->data)->end = *index;
		return (0);
	}
	return (1);
}

int	dquote(char *line, int *index)
{
	remove_char(line, *index);
	ft_list_push_front(&g_info.block_head, create_block_struct(*index, -1));
	while (line[*index] && line[*index] != DQUOTE)
	{
		if (line[*index] == BSLASH)
		{
			if (backslash(line, index, 1))
				return (FAILURE);
		}
		else if (line[*index] == DOLLAR)
			dollar(line, index);
		else
			*index += 1;
	}
	if (!line[*index])
		return (1);
	else if (line[*index] == DQUOTE)
	{
		remove_char(line, *index);
		((t_block *)g_info.block_head->data)->end = *index;
		return (0);
	}
	return (1);
}
