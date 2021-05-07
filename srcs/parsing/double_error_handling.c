/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_error_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:30:24 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/06 18:30:57 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		return (print_err_sep(info, i));
	}
	if (info->line[i] == '>' || info->line[i] == '<')
	{
		i++;
		while (!is_whitespace(info->line[i]))
			i++;
		return (print_err_sep(info, i));
	}
	return (SUCCESS);
}
