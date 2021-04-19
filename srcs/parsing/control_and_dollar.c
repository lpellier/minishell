/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_and_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:11:21 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/18 16:12:44 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	control_d(void)
{
	int		cursor;

	cursor = g_info.cursor.posx - g_info.prompt_len + 1;
	if (g_info.line && g_info.line[cursor])
	{
		remove_char(g_info.line, cursor);
		tputs(tgoto(tgetstr("cm", NULL), g_info.cursor.posx, \
			g_info.cursor.posy), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
	}
	else if (!g_info.line || !g_info.line[0])
	{
		ft_printf("exit");
		g_info.crashed = TRUE;
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

void	dollar_suite(char *line, char *var, int *index, int i)
{
	t_list	*var_list;
	t_env	*var_key;

	var_list = ft_list_find(g_info.env_head, \
		create_env_struct(var, NULL), cmp_env);
	if (var_list)
	{
		var_key = (t_env *)var_list->data;
		i = 0;
		while (var_key->value[i])
		{
			add_char(line, var_key->value[i], *index);
			*index += 1;
			i++;
		}
	}
}

int	dollar(char *line, int *index)
{
	char	*var;
	int		i;

	i = 0;
	if (!line[*index] || !line[*index + 1] || (line[*index + 1] && \
		!ft_isalpha_ordollar(line[*index + 1])))
	{
		*index += 1;
		return (FAILURE);
	}
	if (ft_calloc((void **)&var, 256, sizeof(char)))
		return (FAILURE);
	while (line[*index] && (ft_isalpha(line[*index]) || (line[*index] == \
		DOLLAR && i == 0) || (line[*index] == '?')))
	{
		if (i > 0)
			var[i - 1] = line[*index];
		remove_char(line, *index);
		i++;
	}
	dollar_suite(line, var, index, i);
	return (SUCCESS);
}
