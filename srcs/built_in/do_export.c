/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:49:53 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/24 17:11:59 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** exports a variable to environment
** need to figure out return codes for built in
*/

void	modify_export(char *key, char *value, int concat)
{
	t_env	*env_tmp;

	env_tmp = get_env_custom(key);
	if (!env_tmp)
		ft_list_push_back(&g_info->env_head, \
			create_env_struct(ft_strdup(key), \
			ft_strdup(value)));
	else
		modify_env(key, value, concat);
	secure_free(key);
	secure_free(value);
}

int	export_remove_char(char **key_value)
{
	if (last_char(key_value[0]) == '+')
	{
		remove_char(key_value[0], ft_strlen(key_value[0]) - 1);
		return (1);
	}
	return (0);
}

int	export_error(t_cmd *cmd)
{
	if (cmd->option)
	{
		ft_printf("minisheh: %s: %s: invalid option\n", \
			cmd->cmd, cmd->option);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_export(int index_cmd)
{
	t_cmd	*cmd;
	int		concat;
	char	*key;
	char	*value;
	char	**key_value;

	cmd = ft_list_at(g_info->cmd_head, index_cmd)->data;
	if (export_error(cmd) == FAILURE)
		return (FAILURE);
	if (!cmd->input)
		return (print_declare_env());
	if (!ft_strchr(cmd->input, '='))
		return (FAILURE);
	key_value = ft_split(cmd->input, '=');
	concat = export_remove_char(key_value);
	key = ft_strdup(key_value[0]);
	if (!key_value[1])
		value = ft_strdup("");
	else
		value = ft_strdup(key_value[1]);
	free_tab(&key_value);
	if (str_isalpha_withplus(key) || key[0] == '+')
	{
		ft_printf("minisheh: export: '%s': not a valid identifier\n", \
			cmd->input);
		secure_free(key);
		secure_free(value);
		return (FAILURE);
	}
	modify_export(key, value, concat);
	return (SUCCESS);
}
