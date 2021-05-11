/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backsl_and_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:15:49 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/05 17:52:31 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	backslash(t_info *info, int *index, int dquote)
{
	if (!dquote)
	{
		remove_char(info->line, *index);
		info->lint[*index] = _BSPACED;
		*index += 1;
	}
	else if (dquote)
	{
		if (info->line[*index + 1] && (info->line[*index + 1] == \
			BSLASH || info->line[*index + 1] == DOLLAR || \
			info->line[*index + 1] == DQUOTE))
		{
			remove_char(info->line, *index);
			info->lint[*index] = _BSPACED;
		}
		*index += 1;
	}
	return (SUCCESS);
}

int	is_empty_or_void(int lint)
{
	if (lint == _EMPTY || lint == _EMPTY_CHAR || lint == -1)
		return (SUCCESS);
	return (FAILURE);
}

void	add_empty_char(t_info *info, int count, int index)
{
	if (count == index && index > 0 && \
		!is_empty_or_void(info->lint[index - 1]) && \
		(!info->line[index] || (info->line[index] && info->line[index] == 32)))
	{
		info->lint[index] = _EMPTY_CHAR;
		add_char(info->line, 32, index);
	}
}

int	quote(t_info *info, int *index)
{
	int	count;

	count = *index;
	remove_char(info->line, *index);
	while (info->line[*index] && info->line[*index] != QUOTE)
	{
		info->lint[*index] = _QUOTED;
		*index += 1;
	}
	if (!info->line[*index])
		return (1);
	else if (info->line[*index] == QUOTE)
	{
		remove_char(info->line, *index);
		add_empty_char(info, count, *index);
		return (0);
	}
	return (1);
}

int	dquote(t_info *info, int *index)
{
	int	count;

	count = *index;
	remove_char(info->line, *index);
	while (info->line[*index] && info->line[*index] != DQUOTE)
	{
		info->lint[*index] = _DQUOTED;
		if (info->line[*index] == BSLASH)
			backslash(info, index, 1);
		else
			*index += 1;
	}
	if (!info->line[*index])
		return (1);
	else if (info->line[*index] == DQUOTE)
	{
		remove_char(info->line, *index);
		add_empty_char(info, count, *index);
		return (0);
	}
	return (1);
}
