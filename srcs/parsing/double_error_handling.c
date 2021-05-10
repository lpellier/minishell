/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_error_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:30:24 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/10 13:49:12 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	double_error_syntax(t_info *info, int i, char token)
{
	i++;
	while (info->lint[i] == _EMPTY)
		i++;
	if (info->lint[i] == _SEP && info->line[i] == token)
	{
		ft_printf("minisheh: syntax error near");
		ft_printf(" unexpected token `%c%c'\n", token, token);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	double_redir(t_info *info, int i)
{
	if (info->line[i] && info->lint[i] == _SEP && \
		(info->line[i] == '>' || info->line[i] == '<'))
	{
		i++;
		if (info->line[i] && info->line[i] == '>' && info->lint[i] == _SEP)
			i++;
		while (info->lint[i] == _EMPTY)
			i++;
		if (info->lint[i] == _SEP && info->lint[i + 1] == _SEP && \
			info->line[i] == '>' && info->line[i +1] && info->line[i +1] == '>')
			return (print_error(NULL, NULL, \
				"syntax error near unexpected token `>>'", 1));
		else if (info->lint[i] == _SEP && info->line[i] == '>')
			return (print_error(NULL, NULL, \
				"syntax error near unexpected token `>'", 1));
		else if (info->lint[i] == _SEP && info->line[i] == '<')
			return (print_error(NULL, NULL, \
				"syntax error near unexpected token `<'", 1));
		else if (!info->line[i])
			return (print_error(NULL, NULL, \
				"syntax error near unexpected token `newline'", 1));
	}
	return (SUCCESS);
}
