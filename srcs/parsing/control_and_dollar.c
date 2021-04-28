/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_and_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:11:21 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/27 21:17:22 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	control_d(t_info *info)
{
	int		cursor;

	cursor = info->cursor.posx + info->cursor.posy * info->terminfo.col - info->terminfo.prompt_len;
	if (info->line && info->line[cursor])
	{
		remove_char(info->line, cursor);
		tputs(tgoto(tgetstr("ch", NULL), 1, info->cursor.posx), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
	}
	else if (!info->line || !info->line[0])
	{
		info->crashed = TRUE;
		return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_isalpha_ordollar(int c)
{
	if (c == '?' || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

void	dollar_suite(t_info *info, char *var, int *index, int i, int quote)
{
	t_list	*var_list;
	t_env	*var_key;
	t_env	*data_ref;

	data_ref = create_env_struct(var, NULL);
	var_list = ft_list_find(info->env_head, \
		data_ref, cmp_env);
	secure_free(data_ref);
	secure_free(var);
	if (var_list)
	{
		var_key = (t_env *)var_list->data;
		i = 0;
		while (var_key->value[i])
		{
			add_char(info->line, var_key->value[i], *index);
			if (quote)
				info->lint[*index] = _DQUOTED;
			else
				info->lint[*index] = _CHAR;
			*index += 1;
			i++;
		}
	}
}

int	dollar(t_info *info, int *index, int quote)
{
	char	*var;
	int		i;

	i = 0;
	if (!info->line[*index] || !info->line[*index + 1] || (info->line[*index + 1] && \
		!ft_isalpha_ordollar(info->line[*index + 1])))
	{
		*index += 1;
		return (FAILURE);
	}
	if (ft_calloc((void **)&var, 256, sizeof(char)))
		return (FAILURE);
	while (info->line[*index] && (ft_isalpha(info->line[*index]) || (info->line[*index] == \
		DOLLAR && i == 0) || (info->line[*index] == '?')))
	{
		if (i > 0)
			var[i - 1] = info->line[*index];
		remove_char(info->line, *index);
		i++;
	}
	dollar_suite(info, var, index, i, quote);
	return (SUCCESS);
}
