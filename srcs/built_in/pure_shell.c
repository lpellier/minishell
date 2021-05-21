/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pure_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:26:00 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/21 19:08:18 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	str_is_alpha(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	print_error(char *cmd, char *arg, char *error, int code)
{
	if (cmd && arg && error)
		ft_printf("minisheh: %s: `%s': %s\n", cmd, arg, error);
	else if (arg && error)
		ft_printf("minisheh: %s: %s\n", arg, error);
	else if (error)
		ft_printf("minisheh: %s\n", error);
	return (code);
}

// /*
// ** exits terminal
// */

int	ft_exit(t_info *info, t_cmd *cmd)
{
	int		arg_index;

	arg_index = cmd->arg_index + 1;
	if (cmd->limit_index - arg_index <= 1)
	{
		info->crashed = TRUE;
		if (cmd->args[arg_index] && !int_errors(cmd->args[arg_index]))
			return (print_error("exit", cmd->args[arg_index], \
				"numeric argument required", 2));
		if (cmd->args[arg_index])
			return (ft_atoi(cmd->args[arg_index]));
		return (SUCCESS);
	}
	return (print_error("exit", NULL, "too many arguments", 1));
}

int	arg_is_option(char *arg)
{
	if (arg && arg[0] == '-')
		return (SUCCESS);
	return (FAILURE);
}

// /*
// ** outputs current path
// */

int	ft_pwd(t_info *info, t_cmd *cmd)
{
	char	cwd[PATH_MAX];
	int		arg_index;

	(void)info;
	arg_index = cmd->arg_index + 1;
	if (!arg_is_option(cmd->args[cmd->arg_index]))
		return (print_error(cmd->args[arg_index - 1], \
			cmd->args[arg_index], "invalid option", 1));
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (SUCCESS);
}
