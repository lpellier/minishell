/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:24:33 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/08 14:35:09 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_pipe(char c)
{
	if (c == '|')
		return (SUCCESS);
	else if (c == '\0')
		return (OTHER);
	else
		return (FAILURE);
}

int	is_colon(char c)
{
	if (c == ';')
		return (SUCCESS);
	else if (c == '\0')
		return (OTHER);
	else
		return (FAILURE);
}

int	is_redir_l(char c)
{
	if (c == '<')
		return (SUCCESS);
	else if (c == '\0')
		return (OTHER);
	else
		return (FAILURE);
}

int	is_redir_r(char c)
{
	if (c == '>')
		return (SUCCESS);
	else if (c == '\0')
		return (OTHER);
	else
		return (FAILURE);
}

int	is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (SUCCESS);
	return (FAILURE);
}
