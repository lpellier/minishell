#include "minishell.h"

// is used to reset all of the info after enter is pressed
int    reset_info(t_info *info)
{
	ft_list_clear(info->head);
	return (1);
}

void init_built_in()
{
    built_in[0] = ft_echo;
    built_in[1] = ft_echo_n;
    built_in[2] = ft_exit;
    built_in[3] = ft_pwd;
    built_in[4] = ft_export;
    built_in[5] = ft_unset;
    built_in[6] = ft_env;
    built_in[7] = ft_cd;
}