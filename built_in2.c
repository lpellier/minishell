#include "minishell.h"

// destroys a environment variable from memory
int ft_unset (t_cmd *cmd)
{
    return (0);
}

// outputs all environment variables
int ft_env (t_cmd *cmd)
{
    return (0);
}

// change directory, will need a find function in linked list to check for right bui and right input
int ft_cd (t_cmd *cmd)
{
    // chdir(ft_strjoin(info->cur_path, info->head->input));
    return (0);
}

// actually sets bui according to command string
void    compare_cmd(t_cmd *cmd)
{
    if (!(ft_strncmp(cmd->cmd, "echo -n", 6)))
        cmd->bui = ECHO_N;
    else if (!(ft_strncmp(cmd->cmd, "echo", 4)))
        cmd->bui = ECHO;
    else if (!(ft_strncmp(cmd->cmd, "exit", 4)))
        cmd->bui = EXIT;
    else if (!(ft_strncmp(cmd->cmd, "pwd", 3)))
        cmd->bui = PWD;
    else if (!(ft_strncmp(cmd->cmd, "export", 6)))
        cmd->bui = EXPORT;
    else if (!(ft_strncmp(cmd->cmd, "unset", 5)))
    	cmd->bui = UNSET;
    else if (!(ft_strncmp(cmd->cmd, "env", 3)))
        cmd->bui = ENV;
    else if (!(ft_strncmp(cmd->cmd, "cd", 2)))
        cmd->bui = CD;
    else
        cmd->bui = NONEXISTENT;
}