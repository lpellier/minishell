/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:49:53 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/26 23:47:24 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** exports a variable to environment
** need to figure out return codes for built in
*/

// void	modify_export(t_info *info, char *key, char *value, int concat)
// {
// 	t_env	*env_tmp;

// 	env_tmp = get_env_custom(info, key);
// 	if (!env_tmp)
// 		ft_list_push_back(&info->env_head, \
// 			create_env_struct(ft_strdup(key), \
// 			ft_strdup(value)));
// 	else
// 		modify_env(info, key, value, concat);
// 	secure_free(key);
// 	secure_free(value);
// }

// int	export_remove_char(char **key_value)
// {
// 	if (last_char(key_value[0]) == '+')
// 	{
// 		remove_char(key_value[0], ft_strlen(key_value[0]) - 1);
// 		return (1);
// 	}
// 	return (0);
// }

// int	export_error(t_cmd *cmd)
// {
// 	if (cmd->option)
// 		return (print_error_option(cmd));
// 	return (SUCCESS);
// }

// int	export_content(char *str)
// {
// 	char	*key;
// 	char	*value;
// 	char	**key_value;
// 	int		concat;

// 	if (!ft_strchr(str, '='))
// 		return (FAILURE);
// 	key_value = ft_split(str, '=');
// 	concat = export_remove_char(key_value);
// 	key = ft_strdup(key_value[0]);
// 	if (!key_value[1])
// 		value = ft_strdup("");
// 	else
// 		value = ft_strdup(key_value[1]);
// 	free_tab(&key_value);
// 	if (str_isalpha_withplus(key) || key[0] == '+' || str[0] == '=')
// 	{
// 		ft_printf("minisheh: export: `%s': not a valid identifier\n", \
// 			str);
// 		secure_free(key);
// 		secure_free(value);
// 		return (FAILURE);
// 	}
// 	modify_export(info, key, value, concat);
// 	return (SUCCESS);
// }

int	ft_export()
{
	// t_cmd	*cmd;
	// int		i;
	// int		error;
	// char	**split;

	// cmd = ft_list_at(info->cmd_head, info->index_cmd)->data;
	// if (export_error(cmd))
	// 	return (FAILURE);
	// if (!cmd->input)
	// 	return (print_declare_env());
	// i = 0;
	// error = 0;
	// split = ft_split(cmd->input, 32);
	// while (split[i])
	// {
	// 	error += export_content(split[i]);
	// 	i++;
	// }
	// if (error > 0)
	// 	return (FAILURE);
	return (SUCCESS);
}
