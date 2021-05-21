/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:49:53 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/21 17:59:30 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** exports a variable to environment
** need to figure out return codes for built in
*/

void	modify_export(t_info *info, char *key, char *value)
{
	int		concat;
	t_env	*env_tmp;

	concat = FALSE;
	if (last_char(key) == '+')
	{
		concat = TRUE;
		remove_char(key, ft_strlen(key) - 1);
	}	
	env_tmp = get_env_custom(info, key);
	if (!env_tmp)
		ft_list_push_back(&info->env_head, \
			create_env_struct(ft_strdup(key), \
			ft_strdup(value)));
	else
		modify_env(info, key, value, concat);
	secure_free(key);
	secure_free(value);
}

// error += key_error(key); -> 0 or 1
// error += value_error(key, value); -> 0 or 2

int	export_error(char *str, char *key, char *value )
{
	char	*culprit;
	int		error;

	error = 0;
	error += key_error(key);
	error += value_error(key, value);
	if (error >= 1)
	{
		culprit = ft_strdup(str);
		print_error("export", culprit, "not a valid identifier", 1);
		secure_free(culprit);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	export_content(t_info *info, char *str)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (i < ft_strlen(str))
		key = ft_strndup(str, i);
	else
		return (FAILURE);
	if (i > 0 && str[i - 1] && str[i - 1] == '=')
		value = ft_strdup("");
	else
		value = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	if (export_error(str, key, value))
	{
		secure_free(key);
		secure_free(value);
		return (FAILURE);
	}
	modify_export(info, key, value);
	return (SUCCESS);
}

int	print_declare_env(t_info *info)
{
	char	**sorted;
	int		i;
	int		len;

	i = 0;
	if (!info->env_head || !info->env_head->next)
		return (FAILURE);
	len = ft_list_size(info->env_head->next);
	sorted = ascii_sort(info->env_head->next, len);
	while (i < len)
	{
		print_env_declare(get_env_custom(info, sorted[i]));
		i++;
	}
	return (SUCCESS);
}

int	ft_export(t_info *info, t_cmd *cmd)
{
	int		error;
	int		arg_index;

	error = 0;
	arg_index = cmd->arg_index + 1;
	if (!arg_is_option(cmd->args[arg_index]))
		return (print_error(cmd->args[arg_index - 1], \
			cmd->args[arg_index], "invalid option", 1));
	if (!cmd->args[arg_index])
		return (print_declare_env(info));
	while (cmd->args && cmd->args[arg_index] && arg_index < cmd->limit_index)
	{
		if (!arg_is_empty(cmd, arg_index))
			error += print_error("export", cmd->args[arg_index], \
				"not a valid identifier", 1);
		error += export_content(info, cmd->args[arg_index]);
		arg_index++;
	}
	if (error > 0)
		return (FAILURE);
	return (SUCCESS);
}
