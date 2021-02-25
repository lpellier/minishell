#include "minishell.h"

void    reset_info(t_info *info)
{
    if (info->input)
        free(info->input);
    info->input = ft_strdup("");
    info->option = 0;
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