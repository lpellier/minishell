/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:24:33 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/07 17:26:39 by lpellier         ###   ########.fr       */
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

int	spaces(char *s)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (!s && !s[i])
 		return (FAILURE);
	while (!is_whitespace(s[i]))
	{
		count++;
		i++;
	}
	return (count);
}

// int check_sep(char *line, t_cmd *cmd)
//  {
//  	int i;

//  	i = 0;
//  	if (!line[i])
//  		return (FAILURE);
//  	while (line[i])
//  	{
//  		if (line[i] == '<')
//  			g_info.nb_l_redir++;
//  		else if (line[i] == '>')
//  		{
//  			if (line[i + 1] && line[i + 1] == '>')
//  			{
//  				g_info.nb_rd_redir++;
//  				i++;
//  			}
//  			else
//  				g_info.nb_r_redir++;
//  		}
//  		else if (line[i] == '|')
//  			g_info.nb_pipe++;
//  		else if (line[i] == ';')
//  			g_info.nb_colon++;
//  		i++;
// 	}
// 	if (g_info.nb_l_redir > 0 || g_info.nb_rd_redir > 0 || g_info.nb_r_redir > 0 || g_info.nb_pipe > 0 || g_info.nb_colon > 0)
// 		ft_symbol(cmd);
//  	return (0);
//  }
