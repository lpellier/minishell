/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:56:04 by lpellier          #+#    #+#             */
/*   Updated: 2021/05/06 12:13:51 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_error_syntax(t_info *info, int i)
{
	int	count;

	count = i;
	if (info->line[i] == 124)
	{
		count += 1;
		while (info->line[count])
		{
			if (info->line[count] == COLON)
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

int	double_error_syntax(t_info *info, int i, char token)
{
	if (info->line[i] == token && info->line[i + 1] && \
		info->line[i + 1] == token)
	{
		ft_printf("minisheh: syntax error near");
		ft_printf(" unexpected token `%c%c'\n", token, token);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	double_redir(t_info *info, int i)
{
	if (info->line[i] == '>' && info->line[i + 1] && info->line[i + 1] == '>')
	{
		i += 2;
		while (!is_whitespace(info->line[i]))
			i++;
		if (info->line[i] == '>' && \
			info->line[i + 1] && info->line[i + 1] == '>')
			return (print_error(NULL, NULL, \
				"syntax error near unexpected token `>>'", 1));
		else if (info->line[i] == '>')
			return (print_error(NULL, NULL, \
				"syntax error near unexpected token `>'", 1));
		else if (info->line[i] == '<')
			return (print_error(NULL, NULL, \
				"syntax error near unexpected token `<'", 1));
		else if (!info->line[i])
			return (print_error(NULL, NULL, \
				"syntax error near unexpected token `newline'", 1));
	}
	if (info->line[i] == '>' || info->line[i] == '<')
	{
		i++;
		while (!is_whitespace(info->line[i]))
			i++;
		if (info->line[i] == '>' && \
			info->line[i + 1] && info->line[i + 1] == '>')
			return (print_error(NULL, NULL, \
				"syntax error near unexpected token `>>'", 1));
		else if (info->line[i] == '>')
			return (print_error(NULL, NULL, \
				"syntax error near unexpected token `>'", 1));
		else if (info->line[i] == '<')
			return (print_error(NULL, NULL, \
				"syntax error near unexpected token `<'", 1));
		else if (!info->line[i])
			return (print_error(NULL, NULL, \
				"syntax error near unexpected token `newline'", 1));
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
	if (!info->line)
		return (FAILURE);
	while (!is_whitespace(info->line[i]))
		i++;
	while (info->line[i] && info->line[i] == BSLASH)
		i += 2;
	if (double_error_syntax(info, i, COLON) || \
		double_error_syntax(info, i, 124))
		return (FAILURE);
	if (info->line[i] == COLON || info->line[i] == 124)
		return (syntax_fail(info, i));
	while (info->line[i])
	{
		while (info->line[i] && info->line[i] == BSLASH)
			i += 2;
		if (double_error_syntax(info, i, COLON) || \
			double_error_syntax(info, i, 124) || \
			pipe_error_syntax(info, i) || double_redir(info, i))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
