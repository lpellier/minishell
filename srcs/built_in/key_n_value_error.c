/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_n_value_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:34:46 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/05 16:37:01 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	key_error(char *key)
{
	int		i;

	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '+')
			return (FAILURE);
		i++;
	}
	if (!key || (key && (ft_isdigit(key[0]) || !is_whitespace(key[0]))))
		return (FAILURE);
	return (SUCCESS);
}

int	value_error(char *key, char *value)
{
	if ((key && key[0] == 0) || (value && (value[0] == '=')))
		return (OTHER);
	return (SUCCESS);
}
