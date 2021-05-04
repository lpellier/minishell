/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_and_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:11:21 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/04 14:47:25 by lpellier         ###   ########.fr       */
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

void	dollar_suite(t_info *info, char *cmd_line, char *var, int start, int quote)
{
	int		i;
	int		li;
	t_list	*var_list;
	t_env	*var_key;
	t_env	*data_ref;

	li = info->lint_index + start;
	data_ref = create_env_struct(var, NULL);
	var_list = ft_list_find(info->env_head, data_ref, cmp_env);
	secure_free(data_ref);
	secure_free(var);
	if (!var_list)
	{
		if (quote == TRUE && info->lint[li] == _EMPTY)
		{
			add_char(cmd_line, 32, start);
			add_int(info->lint, _EMPTY_CHAR, li);
		}
		return ;
	}
	var_key = (t_env *)var_list->data;
	i = 0;
	while (var_key->value[i])
	{
		add_char(cmd_line, var_key->value[i], start);
		if (quote)
			add_int(info->lint, _DQUOTED, li);
		else if (var_key->value[i] == 32)
			add_int(info->lint, _EMPTY, li);
		else
			add_int(info->lint, _CHAR, li);
		start++;
		li++;
		i++;
	}
}

int	dollar(t_info *info, char *cmd_line, int start)
{
	char	*var;
	int		j;
	int		li;
	int		quote;

	j = 0;
	li = info->lint_index + start;
	if ((cmd_line[start + 1] && !ft_isalpha(cmd_line[start + 1]) && \
		cmd_line[start + 1] != '?') || !cmd_line[start + 1])
			return (FAILURE);
	remove_char(cmd_line, start);
	remove_int(info->lint, li);
	if (!cmd_line)
		return (FAILURE);
	if (ft_calloc((void **)&var, 256, sizeof(char)))
		return (FAILURE);
	quote = FALSE;
	if (info->lint[li] == _DQUOTED)
		quote = TRUE;
	if (quote)
	{
		while (cmd_line[start] && (ft_isalnum(cmd_line[start]) || \
		cmd_line[start] == '?') && info->lint[li] == _DQUOTED)
		{
			var[j] = cmd_line[start];
			remove_char(cmd_line, start);
			remove_int(info->lint, li);
			j++;
		}
	}
	else
	{
		while (cmd_line[start] && (ft_isalnum(cmd_line[start]) || \
			cmd_line[start] == '?'))
		{
			var[j] = cmd_line[start];
			remove_char(cmd_line, start);
			remove_int(info->lint, li);
			j++;
		}
	}
	dollar_suite(info, cmd_line, var, start, quote);
	return (SUCCESS);
}
