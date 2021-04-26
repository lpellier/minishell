/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:56:04 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/26 23:38:44 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_error_syntax(t_info *info, int i)
{
	int count;

	count = i;
	if (info->line[i] == 124)
	{
		count += 1;
		while (info->line[count])
		{
			if (is_whitespace(info->line[count]))
				return (SUCCESS);
			count++;
		}
		ft_printf("\nminisheh: syntax error near unexpected token `|'\n");
		update_cmd_status(info, 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	double_error_syntax(t_info *info, int i, char token)
{
	if (info->line[i] == token && info->line[i + 1] && \
		info->line[i + 1] == token)
	{
		ft_printf("\nminisheh: syntax error near");
		ft_printf(" unexpected token `%c%c'\n", token, token);
		update_cmd_status(info, 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_syntax(t_info *info)
{
	int		i;

	i = 0;
	if (!info->line)
		return (FAILURE);
	// i += spaces(info->line, i);
	if (double_error_syntax(info, i, COLON) || \
		double_error_syntax(info, i, 124))
		return (FAILURE);
	if (info->line[i] == COLON || info->line[i] == 124)
	{
		ft_printf("\nminisheh: syntax error near");
		ft_printf(" unexpected token `%c'\n", info->line[i]);
		update_cmd_status(info, 2);
		return (FAILURE);
	}
	while (info->line[i])
	{
		if (info->line[i] == BSLASH)
			i += 2;
		if (double_error_syntax(info, i, COLON) || \
			double_error_syntax(info, i, 124) || \
			pipe_error_syntax(info, i))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
