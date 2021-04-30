/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:49:53 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/30 15:47:36 by lpellier         ###   ########.fr       */
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

	concat = 0;
	if (last_char(key) == '+')
	{
		concat = 1;
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
	if (str_isalpha_withplus(key) || key[0] == '+' || str[0] == '=')
	{
		secure_free(key);
		secure_free(value);
		return (print_error("export", str, "not a valid identifier", 1));
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
		error += export_content(info, cmd->args[arg_index]);
		arg_index++;
	}
	if (error > 0)
		return (FAILURE);
	return (SUCCESS);
}
