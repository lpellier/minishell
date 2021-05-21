/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pure_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:26:00 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/21 17:44:40 by lpellier         ###   ########.fr       */
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

int	gross_check(char *arg, int i, int neg)
{
	int	eighteen;

	eighteen = c_to_int(arg[18 + i]);
	if (neg == 0 && eighteen > 7)
		eighteen = 1;
	else if (neg == 1 && eighteen > 8)
		eighteen = 1;
	else
		eighteen = 0;
	if (c_to_int(arg[1 + i]) > 2 || c_to_int(arg[2 + i]) > 2 || \
		c_to_int(arg[3 + i]) > 3 || c_to_int(arg[4 + i]) > 3 || \
		c_to_int(arg[5 + i]) > 7 || c_to_int(arg[6 + i]) > 2 || \
		c_to_int(arg[7 + i]) > 0 || c_to_int(arg[8 + i]) > 3 || \
		c_to_int(arg[9 + i]) > 6 || c_to_int(arg[10 + i]) > 8 || \
		c_to_int(arg[11 + i]) > 5 || c_to_int(arg[12 + i]) > 4 || \
		c_to_int(arg[13 + i]) > 7 || c_to_int(arg[14 + i]) > 7 || \
		c_to_int(arg[15 + i]) > 5 || c_to_int(arg[16 + i]) > 8 || \
		c_to_int(arg[17 + i]) > 0 || eighteen)
		return (SUCCESS);
	else
		return (FAILURE);
}

int	exceeds_limit(char *arg)
{
	int	i;
	int	neg;

	i = 0;
	neg = 0;
	while (arg[i] == '+' || arg[i] == '-')
		i++;
	if (arg[0] == '-')
		neg = 1;
	if (ft_strlen(arg) < 19 + i)
		return (FAILURE);
	else if (ft_strlen(arg) > 19 + i)
		return (SUCCESS);
	return (gross_check(arg, i, neg));
}

int	int_errors(char *arg)
{
	int			i;
	long long	value;

	i = 0;
	while (arg[i] == '+' || arg[i] == '-')
		i++;
	if (i > 1)
		return (SUCCESS);
	if (!str_is_alpha(arg) || !exceeds_limit(arg))
		return (SUCCESS);
	value = ft_llong_atoi(arg);
	return (FAILURE);
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
