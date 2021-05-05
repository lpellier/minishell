/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:09:06 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/05 16:09:55 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_info(t_info *info)
{
	reset_dir_paths(info);
	info->cur_in_history = 0;
	info->terminfo.col = tgetnum("co");
	info->terminfo.lin = tgetnum("li");
	g_signal->kill = FALSE;
	info->cursor.posy = 0;
	g_signal->bin_running = FALSE;
}

int	init_info(t_info *info, char **envp)
{
	t_env	*shlvl;

	info->env_head = ft_create_elem(create_env_struct(ft_strdup("?"), \
		ft_strdup("0")));
	init_env(info, envp);
	if (init_terminal(info))
	{
		ft_list_clear(info->env_head, free_env_struct);
		return (FAILURE);
	}
	if (ft_calloc((void **)&info->line, LINE_MAX, sizeof(char)))
		return (FAILURE);
	if (ft_calloc((void **)&info->lint, LINE_MAX, sizeof(int)))
		return (FAILURE);
	init_built_in(info);
	info->terminfo.echo_padding = 0;
	info->crashed = FALSE;
	shlvl = get_env_custom(info, "SHLVL");
	if (shlvl)
		shlvl->value = ft_itoa(ft_atoi(shlvl->value) + 1);
	reset_info(info);
	return (SUCCESS);
}