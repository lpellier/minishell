/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:05:33 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/18 15:30:36 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	str_isalpha_withplus(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '+')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

char	last_char(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
		i++;
	if (i > 0)
		c = str[i - 1];
	else
		c = '\0';
	return (c);
}

/*
** exports a variable to environment
** need to figure out return codes for built in
*/

int	ft_export(int index_cmd)
{
	t_cmd	*cmd;
	t_env	*env_tmp;
	int		concat;
	char	**key_value;

	cmd = ft_list_at(g_info.cmd_head, index_cmd)->data;
	if (cmd->option)
	{
		ft_printf("minisheh: %s: %s: invalid option\n", \
			cmd->cmd, cmd->option);
		return (FAILURE);
	}
	if (!cmd->input)
		return (print_declare_env());
	if (!ft_strchr(cmd->input, '='))
		return (FAILURE);
	key_value = ft_split(cmd->input, '=');
	concat = 0;
	if (last_char(key_value[0]) == '+')
	{
		remove_char(key_value[0], ft_strlen(key_value[0]) - 1);
		concat = 1;
	}
	if (!key_value[1])
		return (FAILURE);
	if (str_isalpha_withplus(key_value[0]) || key_value[0][0] == '+')
	{
		ft_printf("minisheh: export: '%s': not a valid identifier\n", \
			cmd->input);
		return (FAILURE);
	}
	test(key_value, concat);
	env_tmp = get_env_custom(key_value[0]);
	if (!env_tmp)
		ft_list_push_back(&g_info.env_head, \
			create_env_struct(ft_strdup(key_value[0]), \
			ft_strdup(key_value[1])));
	else
		modify_env(key_value[0], key_value[1], concat);
	free_tab(&key_value);
	return (SUCCESS);
}
