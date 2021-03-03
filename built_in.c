#include "minishell.h"

// outputs input
int ft_echo (t_info *info, int index_cmd)
{
    t_cmd *cmd;

    cmd = ft_list_at(info->cmd_head, index_cmd)->data;
    if (!cmd->input)
        ft_printf("\n");
    else
        ft_printf("%s\n", cmd->input);
    return (SUCCESS);
}

// outputs input without \n
int ft_echo_n (t_info *info, int index_cmd)
{
    t_cmd *cmd;

    cmd = ft_list_at(info->cmd_head, index_cmd)->data;
    if (cmd->input)
        ft_printf("%s\033[47m\033[30m%%\033[39m\033[49m", cmd->input);
    return (SUCCESS);
}

// exits terminal
int ft_exit (t_info *info, int index_cmd)
{
    (void) index_cmd;
    info->crashed = TRUE;
    ft_printf("exit\n");
    return (SUCCESS);
}

// outputs current path
int ft_pwd (t_info *info, int index_cmd)
{
    (void) info;
    (void) index_cmd;
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        ft_printf("%s\n", cwd);
    return (SUCCESS);
}

// exports a variable to environment
// need to figure out return codes for built in
int ft_export (t_info *info, int index_cmd)
{
    t_cmd *cmd;
    char **key_value;

    cmd = ft_list_at(info->cmd_head, index_cmd)->data;
    if (!cmd->input || !ft_strchr(cmd->input, '='))
        return (FAILURE);
    key_value = ft_split(cmd->input, '=');
    if (!key_value[1])
        return (FAILURE);
    ft_list_push_back(&info->env_head, create_env_struct(key_value[0], key_value[1]));
    free(key_value);
    return (SUCCESS);
}
