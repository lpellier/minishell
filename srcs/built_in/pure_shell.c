/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pure_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:26:00 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/25 14:18:53 by lpellier         ###   ########.fr       */
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

int	ft_echo()
{
	t_cmd	*cmd;
	char	*strjoin;
	char	*tmp;

	cmd = ft_list_at(g_info->cmd_head, g_info->index_cmd)->data;
	if (cmd->option && !only_n(cmd->option))
		return (ft_echo_n());
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
	g_info->echo_padding = 0;
	return (SUCCESS);
}

/*
** outputs input without \n
*/

char	*adjust_input_repeated_options(char *input)
{
	int		i;
	char	*ret;
	char	*strjoin;
	char	**split;
	
	i = 0;
	ret = NULL;
	split = ft_split(input, 32);
	while (split[i])
	{
		if (only_n(split[i]))
			break;
		i++;
	}
	while (split[i])
	{
		if (!ret)
			ret = ft_strdup(split[i]);
		else
		{
			strjoin = ft_strjoin(ret, " ");
			ret = ft_strjoin(strjoin, split[i]);
			secure_free(strjoin);
		}
		i++;
	}
	return (ret);
}

int	ft_echo_n()
{
	t_cmd	*cmd;

	cmd = ft_list_at(g_info->cmd_head, g_info->index_cmd)->data;
	if (cmd->input)
		cmd->input = adjust_input_repeated_options(cmd->input);
	if (cmd->input)
		ft_printf("%s", cmd->input);
	g_info->echo_padding = ft_strlen(cmd->input);
	return (SUCCESS);
}

/*
** exits terminal
*/

int	ft_exit()
{
	g_info->crashed = TRUE;
	ft_printf("exit\n");
	return (SUCCESS);
}

/*
** outputs current path
*/

int	ft_pwd()
{
	char	cwd[PATH_MAX];
	t_cmd	*cmd;

	cmd = ft_list_at(g_info->cmd_head, g_info->index_cmd)->data;
	if (cmd->option)
		return (print_error_option(cmd));
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	return (SUCCESS);
}
