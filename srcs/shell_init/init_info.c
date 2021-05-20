/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:09:06 by tefroiss          #+#    #+#             */
/*   Updated: 2021/05/20 12:22:09 by lpellier         ###   ########.fr       */
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
	info->w_cnt = 0;
	info->w_ind = 0;
	info->lnt_ind = 0;
	info->quote = FALSE;
	info->piped = FALSE;
	g_signal->bin_running = FALSE;
}

void	wait_for_children(void)
{
	while (wait(NULL) >= 0)
	{
	}
	g_signal->bin_running = FALSE;
}

void	increment_shlvl(t_info *info)
{
	char	*tmp;
	t_env	*shlvl;

	shlvl = get_env_custom(info, "SHLVL");
	if (shlvl)
	{
		tmp = ft_strdup(shlvl->value);
		secure_free(shlvl->value);
		shlvl->value = ft_itoa(ft_atoi(tmp) + 1);
		secure_free(tmp);
	}
}

int	init_info(t_info *info, char **envp)
{
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
	increment_shlvl(info);
	info->terminfo.echo_padding_x = 0;
	info->crashed = FALSE;
	reset_info(info);
	return (SUCCESS);
}
