#include "minishell.h"

// outputs input
int ft_echo (t_cmd *cmd, char **envp)
{
    (void) envp;
    ft_printf("%s\n", cmd->input);
    return (0);
}

// outputs input without \n
int ft_echo_n (t_cmd *cmd, char **envp)
{
    (void) envp;
    ft_printf("%s\033[47m\033[30m%%\033[39m\033[49m", cmd->input);
    return (0);
}

// exits terminal
int ft_exit (t_cmd *cmd, char ** envp)
{
    (void) envp;
    ft_printf("%s\n", cmd->cmd);
    exit (0);
}

// outputs current path
int ft_pwd (t_cmd *cmd, char ** envp)
{
    (void) envp;
    (void)cmd;
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        ft_printf("%s\n", cwd);
    return (0);
}

// exports a variable to environnment
int ft_export (t_cmd *cmd, char ** envp)
{
    (void) envp;
    (void) cmd;
    return (0);
}
