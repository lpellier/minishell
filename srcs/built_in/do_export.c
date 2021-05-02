/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:49:53 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/01 18:11:03 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** exports a variable to environment
** need to figure out return codes for built in
*/

void		modify_export(t_info *info, char *key, char *value)
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

int value_error(char *key, char *value)
{
	if ((key && key[0] == 0) || (value && (value[0] == '=')))
		return (OTHER);
	return (SUCCESS);
}

int	export_error(char *str, char *key, char *value )
{
	char	*culprit;
	int		error;

	error = 0;
	error += key_error(key); // 0 or 1
	error += value_error(key, value); // 0 or 2
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
	if (str[i - 1] && str[i - 1] == '=')
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
	if (!info->env_head || !info->env_head->next)
		return (FAILURE);
	ft_list_foreach(info->env_head->next, print_env_declare);
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
		if (cmd->lint[arg_index][0] == _EMPTY_CHAR)
			error += print_error("export", cmd->args[arg_index], "not a valid identifier", 1);
		else
			error += export_content(info, cmd->args[arg_index]);
		arg_index++;
	}
	if (error > 0)
		return (FAILURE);
	return (SUCCESS);
}
