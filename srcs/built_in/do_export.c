/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:49:53 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/18 15:58:12 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** exports a variable to environment
** need to figure out return codes for built in
*/

void	modify_export(char **key_value, int concat)
{
	t_env	*env_tmp;

	env_tmp = get_env_custom(key_value[0]);
	if (!env_tmp)
		ft_list_push_back(&g_info.env_head, \
			create_env_struct(ft_strdup(key_value[0]), \
			ft_strdup(key_value[1])));
	else
		modify_env(key_value[0], key_value[1], concat);
	free_tab(&key_value);
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
	char	**key_value;

	cmd = ft_list_at(g_info.cmd_head, index_cmd)->data;
	if (export_error(cmd) == FAILURE)
		return (FAILURE);
	if (!cmd->input)
		return (print_declare_env());
	if (!ft_strchr(cmd->input, '='))
		return (FAILURE);
	key_value = ft_split(cmd->input, '=');
	concat = export_remove_char(key_value);
	if (!key_value[1])
		return (FAILURE);
	if (str_isalpha_withplus(key_value[0]) || key_value[0][0] == '+')
	{
		ft_printf("minisheh: export: '%s': not a valid identifier\n", \
			cmd->input);
		return (FAILURE);
	}
	modify_export(key_value, concat);
	return (SUCCESS);
}
