/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:24:33 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/30 17:39:23 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			is_pipe(char c)
{
	if (c == '|')
		return (SUCCESS);
	else if (c == '\0')
		return (OTHER);
	else
		return (FAILURE);
}

int			is_colon(char c)
{
	if (c == ';')
		return (SUCCESS);
	else if (c == '\0')
		return (OTHER);
	else
		return (FAILURE);
}

int			is_redir(char c)
{
	if (c == '<' || c == '>')
		return (SUCCESS);
	else if (c == '\0')
		return (OTHER);
	else
		return (FAILURE);
}

int			is_whitespace(char c)
{
    if (c == 32 || (c >= 9 && c <= 13))
        return (SUCCESS);
    return (FAILURE);
}

int			spaces(char *s)
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

// int check_sep(char *line)
// {
// 	int i;

// 	i = 0;
// 	if (!line[i])
// 		return (FAILURE);
// 	while (line[i])
// 	{
// 		if (line[i] == '<')
// 			info.nb_l_redir++;
// 		else if (line[i] == '>')
// 		{
// 			if (line[i + 1] && line[i + 1] == '>')
// 			{
// 				info.nb_rd_redir++;
// 				i++;
// 			}
// 			else
// 				info.nb_r_redir++;
// 		}
// 		else if (line[i] == '|')
// 			info.nb_pipe++;
// 		else if (line[i] == ';')
// 			info.nb_colon++;
// 		i++;
// 	}
// 	return (0);
// }
