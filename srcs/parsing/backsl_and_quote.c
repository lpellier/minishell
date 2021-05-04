/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backsl_and_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:15:49 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/01 18:00:25 by lpellier         ###   ########.fr       */
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
		if (info->line[*index + 1] && (info->line[*index + 1] == BSLASH || \
			info->line[*index + 1] == DOLLAR || info->line[*index + 1] == DQUOTE))
		{
			remove_char(info->line, *index);
			info->lint[*index] = _BSPACED;
		}
		*index += 1;
	}
	return (SUCCESS);
}

int		is_empty_or_void(int lint)
{
	if (lint == _EMPTY || lint == _EMPTY_CHAR || lint == -1)
		return (SUCCESS);
	return (FAILURE);
}

void	add_empty_char(t_info *info, int count, int index)
{
	if (count == index && !is_empty_or_void(info->lint[index - 1]) && \
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

int	transform_line(t_info *info, int index, int quote_nb, int dquote_nb)
{
	int		ret;

	ret = 0;
	while (info->line[index] && info->line[index] != BSLASH && \
		info->line[index] != QUOTE && info->line[index] != DQUOTE)
	{
		if (info->lint[index] == -1 && info->line[index] == 32)
			info->lint[index] = _EMPTY;
		else if (!ft_cinset(info->line[index], SEPARATOR))
			info->lint[index] = _SEP;
		else if (info->line[index] == '$')
			info->lint[index] = _DOLLAR;
		else if (info->lint[index] == -1)
			info->lint[index] = _CHAR;
		if (index > 0 && info->line[index - 1] != 32 && info->lint[index - 1] != _SEP && \
			!ft_cinset(info->line[index], SEPARATOR) && info->lint[index] == _SEP)
		{
			info->lint[index] = _EMPTY;
			add_char(info->line, 32, index);
		}
		if (info->line[index + 1] != 32 && info->line[index + 1] != '>' && \
			!ft_cinset(info->line[index], SEPARATOR) && info->lint[index] == _SEP)
		{
			info->lint[index + 1] = _EMPTY;
			add_char(info->line, 32, index + 1);
		}
		index++;
	}
	if (info->line[index] == QUOTE)
		quote_nb += quote(info, &index);
	else if (info->line[index] == DQUOTE)
		dquote_nb += dquote(info, &index);
	else if (info->line[index] == BSLASH)
		backslash(info, &index, 0);
	if (info->line[index])
		ret = transform_line(info, index, quote_nb, dquote_nb);
	else
		ret = count_exceptions(quote_nb, dquote_nb);
	return (ret);
}
