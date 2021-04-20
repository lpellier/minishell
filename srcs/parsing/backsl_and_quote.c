/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backsl_and_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:15:49 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/20 18:52:09 by lpellier         ###   ########.fr       */
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
		if (line[*index + 1] && (line[*index + 1] == BSLASH || \
			line[*index + 1] == '$' || line[*index + 1] == DQUOTE))
		{
			remove_char(line, *index);
			if (!line[*index + 1])
				return (FAILURE);
		}
		*index += 1;
	}
	return (SUCCESS);
}

int	quote(char *line, int *index)
{
	remove_char(line, *index);
	ft_list_push_front(&g_info->block_head, create_block_struct(*index, -1));
	while (line[*index] && line[*index] != QUOTE)
		*index += 1;
	if (!line[*index])
		return (1);
	else if (line[*index] == QUOTE)
	{
		remove_char(line, *index);
		((t_block *)g_info->block_head->data)->end = *index;
		return (0);
	}
	return (1);
}

int	dquote(char *line, int *index)
{
	remove_char(line, *index);
	ft_list_push_front(&g_info->block_head, create_block_struct(*index, -1));
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
		((t_block *)g_info->block_head->data)->end = *index;
		return (0);
	}
	return (1);
}

int	transform_line(char *line, int index, int quote_nb, int dquote_nb)
{
	int		ret;

	ret = 0;
	while (line[index] && line[index] != BSLASH && line[index] != QUOTE && \
		line[index] != DQUOTE && line[index] != DOLLAR)
		index++;
	if (line[index] == BSLASH)
		backslash(line, &index, 0);
	if (line[index] == DOLLAR)
		dollar(line, &index);
	if (line[index] == QUOTE)
		quote_nb += quote(line, &index);
	if (line[index] == DQUOTE)
		dquote_nb += dquote(line, &index);
	if (line[index])
		ret = transform_line(line, index, quote_nb, dquote_nb);
	else
		ret = count_exceptions(quote_nb, dquote_nb);
	return (ret);
}
