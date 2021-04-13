/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:05:33 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/13 15:00:26 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** outputs input
*/

int	only_n(char *str)
{
	int		i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	ft_echo(int index_cmd)
{
	t_cmd	*cmd;
	char	*tmp;

	cmd = ft_list_at(g_info.cmd_head, index_cmd)->data;
	if (cmd->option && !only_n(cmd->option))
		return (ft_echo_n(index_cmd));
	else if (cmd->option)
	{
		if (cmd->input)
		{
			tmp = ft_strdup(cmd->input);
			free(cmd->input);
			cmd->input = ft_strjoin(ft_strjoin(cmd->option, " "), tmp);
		}
	}
	if (!cmd->input)
		ft_printf("\n");
	else
		ft_printf("%s\n", cmd->input);
	return (SUCCESS);
}

// void	store_output(int index_cmd)
// {
// 	char	*str;
// 	t_cmd	*cmd;

// 	cmd = (t_cmd *)ft_list_at(g_info.cmd_head, index_cmd)->data;
// 	get_next_line(STDIN_FILENO, &str);
// 	g_info.output = ft_strdup(str);
// 	if (cmd->bui != 1 && cmd->bui != 9)
// 		g_info.output = ft_strjoin(str, "\n");
// 	else
// 		g_info.output = ft_strdup(str);
// 	while (get_next_line(STDIN_FILENO, &str))
// 	{
// 		if (cmd->bui != 1 && cmd->bui != 9)
// 			g_info.output = ft_strjoin(ft_strjoin(g_info.output, str), "\n");
// 		else
// 			g_info.output = ft_strjoin(g_info.output, str);
// 	}
// 	if (str)
// 		free(str);
// 	str = NULL;
// }

/*
** outputs input without \n
*/

int	ft_echo_n(int index_cmd)
{
	t_cmd	*cmd;

	cmd = ft_list_at(g_info.cmd_head, index_cmd)->data;
	if (cmd->input)
		ft_printf("%s\033[47m\033[30m%%\033[39m\033[49m", cmd->input);
	g_info.echo_padding = ft_strlen(cmd->input) + 1;
	return (SUCCESS);
}

/*
** exits terminal
*/

int	ft_exit(int index_cmd)
{
	(void)index_cmd;
	g_info.crashed = TRUE;
	ft_printf("exit\n");
	return (SUCCESS);
}

/*
** outputs current path
*/

int	ft_pwd(int index_cmd)
{
	char	cwd[PATH_MAX];
	t_cmd	*cmd;

	cmd = ft_list_at(g_info.cmd_head, index_cmd)->data;
	if (cmd->option)
	{
		ft_printf("minisheh: %s: %s: invalid option\n", cmd->cmd, cmd->option);
		return (FAILURE);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	return (SUCCESS);
}

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
