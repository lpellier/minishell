/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_and_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:11:21 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/03 12:12:29 by lpellier         ###   ########.fr       */
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

void	dollar_suite(t_info *info, t_cmd *cmd, int arg_index, char *var, int start, int quote)
{
	int		i;
	t_list	*var_list;
	t_env	*var_key;
	t_env	*data_ref;

	data_ref = create_env_struct(var, NULL);
	var_list = ft_list_find(info->env_head, data_ref, cmp_env);
	secure_free(data_ref);
	secure_free(var);
	if (!var_list)
	{
		add_int(cmd->lint[arg_index], _EMPTY_CHAR, start);
		return ;
	}
	var_key = (t_env *)var_list->data;
	i = 0;
	while (var_key->value[i])
	{
		add_char(cmd->args[arg_index], var_key->value[i], start);
		if (quote)
			add_int(cmd->lint[arg_index], _DQUOTED, start);
		else
			add_int(cmd->lint[arg_index], _CHAR, start);
		start++;
		i++;
	}
	if (i == 0)
		add_int(cmd->lint[arg_index], _EMPTY_CHAR, start);
}

int	dollar(t_info *info, t_cmd *cmd, int arg_index, int start)
{
	char	*var;
	int		j;
	int		quote;

	j = 0;
	if ((cmd->args[arg_index][start + 1] && !ft_isalpha(cmd->args[arg_index][start + 1]) && \
		cmd->args[arg_index][start + 1] != '?') || !cmd->args[arg_index][start + 1])
			return (FAILURE);
	secure_free(cmd->saved_env_arg);
	cmd->saved_env_arg = ft_strdup(cmd->args[arg_index]);
	remove_char(cmd->args[arg_index], start);
	remove_int(cmd->lint[arg_index], start);
	if (!cmd->args[arg_index])
		return (FAILURE);
	if (ft_calloc((void **)&var, 256, sizeof(char)))
		return (FAILURE);
	quote = FALSE;
	if (cmd->lint[arg_index][start] == _DQUOTED)
		quote = TRUE;
	while (cmd->args[arg_index][start] && \
		(ft_isalnum(cmd->args[arg_index][start]) || \
			cmd->args[arg_index][start] == '?'))
	{
		var[j] = cmd->args[arg_index][start];
		remove_char(cmd->args[arg_index], start);
		remove_int(cmd->lint[arg_index], start);
		j++;
	}
	dollar_suite(info, cmd, arg_index, var, start, quote);
	return (SUCCESS);
}
