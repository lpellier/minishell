#include "minishell.h"

// destroys a environment variable from memory
int ft_unset (t_cmd *cmd)
{
    (void) cmd;
    return (0);
}

// outputs all environment variables
int ft_env (t_cmd *cmd)
{
    (void) cmd;

    return (0);
}

// change directory, will need a find function in linked list to check for right bui and right input
int ft_cd (t_cmd *cmd)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        if (chdir(ft_strjoin(cwd, cmd->input)))
            ft_printf("Couldn't access folder, check directory listing\n%s\n", ft_strjoin(ft_strjoin(cwd, "/"), cmd->input));
    }
    else
        ft_printf("Error\n");
    // chdir(ft_strjoin(info->cur_path, info->head->input));
    return (0);
}

//int ft_inpath (t_cmd *cmd)
//{
//    (void) cmd;
//    // chdir(ft_strjoin(info->cur_path, info->head->input));
//    return (0);
//}
// actually sets bui according to command string
void    compare_cmd(t_cmd *cmd)
{
    if (!(ft_strncmp(cmd->cmd, "echo", 4)) && cmd->option && !(ft_strncmp(cmd->option, "-n", 2)))
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
    else // here we'll need to check for $PATH and exec binaries if when find them
        cmd->bui = NONEXISTENT;
}
