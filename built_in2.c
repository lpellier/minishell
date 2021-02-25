#include "minishell.h"

int ft_unset (char *cmd, t_info *info)
{
    return (0);
}
int ft_env (char *cmd, t_info *info)
{
    return (0);
}
int ft_cd (char *cmd, t_info *info)
{
    chdir(ft_strjoin(info->cur_path, info->input));
    return (0);
}

void    compare_cmd(char *cmd, enum built_in_index *bui)
{
    if (!(ft_strncmp(cmd, "echo-n", 6)))
        *bui = ECHO_N;
    else if (!(ft_strncmp(cmd, "echo", 4)))
        *bui = ECHO;
    else if (!(ft_strncmp(cmd, "exit", 4)))
        *bui = EXIT;
    else if (!(ft_strncmp(cmd, "pwd", 3)))
        *bui = PWD;
    else if (!(ft_strncmp(cmd, "export", 6)))
        *bui = EXPORT;
    else if (!(ft_strncmp(cmd, "unset", 5)))
        *bui = UNSET;
    else if (!(ft_strncmp(cmd, "env", 3)))
        *bui = ENV;
    else if (!(ft_strncmp(cmd, "cd", 2)))
        *bui = CD;
    else
        *bui = NONEXISTENT;
}