/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:56:04 by lpellier          #+#    #+#             */
/*   Updated: 2021/05/10 13:51:34 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_error_syntax(t_info *info, int i)
{
	int	count;

	count = i;
	if (info->line[i] == 124 && info->lint[count] == _SEP)
	{
		count += 1;
		while (info->line[count])
		{
			if (info->line[count] == COLON && info->lint[count] == _SEP)
				return (print_error(NULL, NULL, \
					"syntax error near unexpected token `;'", 1));
			if (is_whitespace(info->line[count]))
				return (SUCCESS);
			count++;
		}
		ft_printf("minisheh: syntax error near unexpected token `|'\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	syntax_fail(t_info *info, int i)
{
	ft_printf("minisheh: syntax error near");
	ft_printf(" unexpected token `%c'\n", info->line[i]);
	return (FAILURE);
}

int	check_syntax(t_info *info)
{
	int		i;

	i = 0;
	if (!info->line || !info->lint)
		return (FAILURE);
	while (info->lint[i] == _EMPTY)
		i++;
	if (info->lint[i] == _SEP && (double_error_syntax(info, i, COLON) || \
		double_error_syntax(info, i, 124)))
		return (FAILURE);
	if (info->lint[i] == _SEP && (info->line[i] == COLON || \
		info->line[i] == 124))
		return (syntax_fail(info, i));
	while (info->line[i])
	{
		if (info->lint[i] == _SEP && (double_error_syntax(info, i, COLON) || \
			double_error_syntax(info, i, 124) || pipe_error_syntax(info, i) || \
			double_redir(info, i)))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
