#include "minishell.h"

// destroys a environment variable from memory
// needs a delete linked list chain function
int ft_unset (t_info *info, int index_cmd)
{
    t_cmd *cmd;

    cmd = ft_list_at(info->cmd_head, index_cmd)->data;
    ft_list_remove_if(&info->env_head, create_env_struct(cmd->input, NULL), cmp_env, free_env_struct);

    return (SUCCESS);
}

// outputs all environment variables
int ft_env (t_info *info, int index_cmd)
{
    (void) index_cmd;

    if (!info->env_head || !info->env_head->next)
        return (FAILURE);
    ft_list_foreach(info->env_head->next, print_env_struct);
    return (SUCCESS);
}

// change directory, will need a find function in linked list to check for right bui and right input
int ft_cd (t_info *info, int index_cmd)
{
    t_cmd *cmd;
    char cwd[PATH_MAX];

    cmd = ft_list_at(info->cmd_head, index_cmd)->data;
    if (!cmd->input)
    {
        if (chdir("~"))
            ft_printf("Couldn't access folder, check directory listing\n");
    }
    else if (cmd->input[0] == '/')
    {
        if (chdir(cmd->input))
            ft_printf("Couldn't access folder, check directory listing\n");
    }
    else if (getcwd(cwd, sizeof(cwd)))
    {
        if (chdir(ft_strjoin(ft_strjoin(cwd, "/"), cmd->input)))
            ft_printf("Couldn't access folder, check directory listing\n");
    }
    else
        ft_printf("Error\n");
    return (SUCCESS);
}

int exec_binary(t_info *info, int index_cmd)
{
    (void) info;
    (void) index_cmd;
    return (0);
}

int    compare_size(char *s1, char *s2)
{
    int len1;
    int len2;

    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    if (!ft_strncmp(s1, s2, len1) && len1 == len2)
        return (SUCCESS);
    else
        return (FAILURE);
}

int     find_binary(t_info *info, t_cmd *cmd)
{
    int i;

    i = 0;
    while (info->dir_paths[i])
    {
        if (!directories(info->dir_paths[i], cmd->cmd))
        {
            cmd->path = ft_strjoin(ft_strjoin(info->dir_paths[i], "/"), cmd->cmd);
            ft_printf("binary path : %s\n", cmd->path);
            return (SUCCESS);
        }
        i++;
    }
    return (FAILURE);
}

void    compare_cmd(t_info *info, t_cmd *cmd)
{
    if (!cmd->cmd)
        cmd->bui = NONEXISTENT;
    else if (!compare_size(cmd->cmd, "echo") && cmd->option && !compare_size(cmd->option, "-n"))
        cmd->bui = ECHO_N; // 1
    else if (!compare_size(cmd->cmd, "echo"))
        cmd->bui = ECHO; // 0
    else if (!compare_size(cmd->cmd, "exit"))
        cmd->bui = EXIT; // 2
    else if (!compare_size(cmd->cmd, "pwd"))
        cmd->bui = PWD; // etc
    else if (!compare_size(cmd->cmd, "export"))
        cmd->bui = EXPORT;
    else if (!compare_size(cmd->cmd, "unset"))
    	cmd->bui = UNSET;
    else if (!compare_size(cmd->cmd, "env"))
        cmd->bui = ENV;
    else if (!compare_size(cmd->cmd, "cd"))
        cmd->bui = CD; // 7
    else if (!find_binary(info, cmd))
        cmd->bui = BINARY; // 8
    else
        cmd->bui = NONEXISTENT; // 9
}
