#include "minishell.h"

// outputs input
int ft_echo (t_info *info, int index_cmd)
{
    t_cmd *cmd;

    cmd = ft_list_at(info->cmd_head, index_cmd)->data;
    ft_printf("%s\n", cmd->input);
    return (0);
}

// outputs input without \n
int ft_echo_n (t_info *info, int index_cmd)
{
    t_cmd *cmd;

    cmd = ft_list_at(info->cmd_head, index_cmd)->data;
    ft_printf("%s\033[47m\033[30m%%\033[39m\033[49m", cmd->input);
    return (0);
}

// exits terminal
int ft_exit (t_info *info, int index_cmd)
{
    (void) index_cmd;
    info->crashed = TRUE;
    ft_printf("exit\n");
    return (0);
}

// outputs current path
int ft_pwd (t_info *info, int index_cmd)
{
    (void) info;
    (void) index_cmd;
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        ft_printf("%s\n", cwd);
    return (0);
}

// exports a variable to environnment
// need to figure out return codes for built in
int ft_export (t_info *info, int index_cmd)
{
    t_cmd *cmd;
    char **key_value;

    cmd = ft_list_at(info->cmd_head, index_cmd)->data;
    if (!cmd->input || !ft_strchr(cmd->input, '='))
        return (1);
    key_value = ft_split(cmd->input, '=');
    if (!key_value[1])
        return (1);
    ft_list_push_back(&info->env_head, create_env_struct(key_value[0], key_value[1]));
    free(key_value);
    return (0);
}
