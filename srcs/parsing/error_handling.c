/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:56:04 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/25 21:37:24 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_error_syntax(int i)
{
	int count;

	count = i;
	if (g_info->line[i] == 124)
	{
		count += 1;
		while (g_info->line[count])
		{
			if (is_whitespace(g_info->line[count]))
				return (SUCCESS);
			count++;
		}
		ft_printf("\nminisheh: syntax error near unexpected token `|'\n");
		g_info->cmd_status = 2;
		update_cmd_status();
		return (FAILURE);
	}
	return (SUCCESS);
}

int	double_error_syntax(int i, char token)
{
	if (g_info->line[i] == token && g_info->line[i + 1] && \
		g_info->line[i + 1] == token)
	{
		ft_printf("\nminisheh: syntax error near");
		ft_printf(" unexpected token `%c%c'\n", token, token);
		g_info->cmd_status = 2;
		update_cmd_status();
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_syntax(void)
{
	int		i;

	i = 0;
	if (!g_info->line)
		return (FAILURE);
	i += spaces(g_info->line, i);
	if (double_error_syntax(i, COLON) || double_error_syntax(i, 124))
		return (FAILURE);
	if (g_info->line[i] == COLON || g_info->line[i] == 124)
	{
		ft_printf("\nminisheh: syntax error near");
		ft_printf(" unexpected token `%c'\n", g_info->line[i]);
		g_info->cmd_status = 2;
		update_cmd_status();
		return (FAILURE);
	}
	while (g_info->line[i])
	{
		if (g_info->line[i] == BSLASH)
			i += 2;
		if (double_error_syntax(i, COLON) || double_error_syntax(i, 124) || \
			pipe_error_syntax(i))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}