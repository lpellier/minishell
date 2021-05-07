/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_n_doll_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:45:38 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/06 20:54:45 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_something(char *cmd_line, int start, t_info *info, int li)
{
	add_char(cmd_line, 32, start);
	add_int(info->lint, _EMPTY_CHAR, li);
}

int	add_if_something(int li, t_info *info, int i, t_env *var)
{
	if (info->quote)
		add_int(info->lint, _DQUOTED, li);
	else if (var->value[i] == 32)
		add_int(info->lint, _EMPTY, li);
	else
		add_int(info->lint, _DOLLARED, li);
	return (1);
}

void	combine_secure_free(t_env *data_ref, char *var)
{
	secure_free(data_ref);
	secure_free(var);
}
