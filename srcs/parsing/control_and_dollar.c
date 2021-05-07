/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_and_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:11:21 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/07 15:23:13 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	control_d(t_info *info)
{
	int		cursor;

	cursor = info->cursor.posx + info->cursor.posy * \
		info->terminfo.col - info->terminfo.prompt_len;
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

void
	dollar_suite(t_info *info, char *cmd_line, char *var, int start)
{
	int		i;
	int		li;
	t_list	*var_list;
	t_env	*var_key;
	t_env	*data_ref;

	li = info->lint_index + start;
	data_ref = create_env_struct(var, NULL);
	var_list = ft_list_find(info->env_head, data_ref, cmp_env);
	combine_secure_free(data_ref, var);
	if (!var_list)
	{
		if (info->quote == TRUE && info->lint[li] == _EMPTY)
			add_something(cmd_line, start, info, li);
		return ;
	}
	var_key = (t_env *)var_list->data;
	i = 0;
	while (var_key->value[i])
	{
		add_char(cmd_line, var_key->value[i], start);
		li += add_if_something(li, info, i, var_key);
		start++;
		i++;
	}
}

char	delete_dollar(t_info *info, char *cmd_line, int start, int *j)
{
	int		li;
	char	tmp;

	li = info->lint_index + start;
	tmp = cmd_line[start];
	remove_char(cmd_line, start);
	remove_int(info->lint, li);
	(*j)++;
	return (tmp);
}

void	dollar_removal(t_info *info, char *cmd_line, char *var, int start)
{
	int	li;
	int	j;

	j = 0;
	li = info->lint_index + start;
	info->quote = FALSE;
	if (info->lint[li] == _DQUOTED)
		info->quote = TRUE;
	if (info->quote)
	{
		while (cmd_line[start] && (ft_isalnum(cmd_line[start]) || \
			cmd_line[start] == '?') && info->lint[li] == _DQUOTED)
			var[j - 1] = delete_dollar(info, cmd_line, start, &j);
	}
	else
	{
		while (cmd_line[start] && (ft_isalnum(cmd_line[start]) || \
			cmd_line[start] == '?'))
			var[j - 1] = delete_dollar(info, cmd_line, start, &j);
	}
}

int	dollar(t_info *info, char *cmd_line, int start)
{
	char	*var;
	int		li;

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
	dollar_removal(info, cmd_line, var, start);
	dollar_suite(info, cmd_line, var, start);
	return (SUCCESS);
}
