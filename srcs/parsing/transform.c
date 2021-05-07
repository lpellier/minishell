/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 17:52:06 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/06 15:38:31 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	what_is_this_lint(t_info *info, int index)
{
	if (info->lint[index] == -1 && info->line[index] == 32)
		info->lint[index] = _EMPTY;
	else if (!ft_cinset(info->line[index], SEPARATOR))
		info->lint[index] = _SEP;
	else if (info->line[index] == '$')
		info->lint[index] = _DOLLAR;
	else if (info->lint[index] == -1)
		info->lint[index] = _CHAR;
}

void	what_is_this_line(t_info *info, int index)
{
	if (index > 0 && info->line[index - 1] != 32 && \
		info->lint[index - 1] != _SEP && !ft_cinset(info->line[index], \
		SEPARATOR) && info->lint[index] == _SEP)
	{
		info->lint[index] = _EMPTY;
		add_char(info->line, 32, index);
	}
	if (info->line[index + 1] != 32 && info->line[index + 1] != '>' && \
		!ft_cinset(info->line[index], SEPARATOR) \
		&& info->lint[index] == _SEP)
	{
		info->lint[index + 1] = _EMPTY;
		add_char(info->line, 32, index + 1);
	}
}

int	transform_line(t_info *info, int index, int quote_nb, int dquote_nb)
{
	int		ret;

	ret = 0;
	while (info->line[index] && info->line[index] != BSLASH && \
		info->line[index] != QUOTE && info->line[index] != DQUOTE)
	{
		what_is_this_lint(info, index);
		what_is_this_line(info, index);
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
