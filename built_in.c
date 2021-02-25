#include "minishell.h"

int ft_echo (char *cmd, t_info *info)
{
    ft_printf("%s\n", info->input);
    return (0);
}

int ft_echo_n (char *cmd, t_info *info)
{
    ft_printf("%s\033[47m\033[30m%%\033[39m\033[49m", info->input);
    return (0);
}

int ft_exit (char *cmd, t_info *info)
{
    exit (0);
}
int ft_pwd (char *cmd, t_info *info)
{
    return (0);
}
int ft_export (char *cmd, t_info *info)
{
    return (0);
}