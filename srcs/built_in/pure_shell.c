/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pure_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:26:00 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/21 14:30:48 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	char	*strjoin;
	char	*tmp;

	cmd = ft_list_at(g_info->cmd_head, index_cmd)->data;
	g_info->status = 0;
	if (cmd->option && !only_n(cmd->option))
		return (ft_echo_n(index_cmd));
	else if (cmd->option)
	{
		if (cmd->input)
		{
			tmp = ft_strdup(cmd->input);
			free(cmd->input);
			strjoin = ft_strjoin(cmd->option, " ");
			cmd->input = ft_strjoin(strjoin, tmp);
			secure_free(strjoin);
		}
		else
			cmd->input = ft_strdup(cmd->option);
	}
	if (!cmd->input)
		ft_printf("\n");
	else
		ft_printf("%s\n", cmd->input);
	return (SUCCESS);
}

/*
** outputs input without \n
*/

int	ft_echo_n(int index_cmd)
{
	t_cmd	*cmd;

	cmd = ft_list_at(g_info->cmd_head, index_cmd)->data;
	if (cmd->input)
		ft_printf("%s\033[47m\033[30m%%\033[39m\033[49m", cmd->input);
	g_info->echo_padding = ft_strlen(cmd->input) + 1;
	return (SUCCESS);
}

/*
** exits terminal
*/

int	ft_exit(int index_cmd)
{
	(void)index_cmd;
	g_info->crashed = TRUE;
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

	cmd = ft_list_at(g_info->cmd_head, index_cmd)->data;
	if (cmd->option)
	{
		ft_printf("minisheh: %s: %s: invalid option\n", cmd->cmd, cmd->option);
		return (FAILURE);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	return (SUCCESS);
}
