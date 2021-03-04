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

void store_output(t_cmd *cmd)
{
    char *str;

    get_next_line(STDIN_FILENO, &str);
    cmd->output = ft_strdup(str);
    if (cmd->bui != 1 && cmd->bui != 9)
        cmd->output = ft_strjoin(str, "\n"); // storing it in output variable
    else
        cmd->output = ft_strdup(str);
    while (get_next_line(STDIN_FILENO, &str))
    {
        if (cmd->bui != 1 && cmd->bui != 9)
            cmd->output = ft_strjoin(ft_strjoin(cmd->output, str), "\n"); // storing it in output variable
        else
            cmd->output = ft_strjoin(cmd->output, str);
    }
    if (str)
        free(str);
    str = NULL;
}

int pipe_for_exec(t_info *info, int index_cmd)
{
    // stores fd extremes from pipe : pipefd[0] is reading and pipefd[1] is writing
    int pipefd[2];
    // cpid is child process id returned by fork
    pid_t cpid, saved_stdin, saved_stdout;
    t_cmd *cmd;
    // status is basically the return code of any command, returned by waitpid, might be useful to store it
    int status;

    cmd = ft_list_at(info->cmd_head, index_cmd)->data;
    // saving std output and input fds
    saved_stdin = dup(STDIN_FILENO);
    saved_stdout = dup(STDOUT_FILENO);
    if (pipe(pipefd) == -1)
        exit(EXIT_FAILURE);
    cpid = fork(); // forking so i can retrieve output of each function for piping
    if (cpid == -1)
        exit(EXIT_FAILURE);
    if (cpid == 0)
    {
         close(pipefd[0]); // closing useless writing extremity of pipe
         dup2(pipefd[1], STDOUT_FILENO); // duplicating reading extremity of pipe into stdout so i can
         // print cmd to retrieve output
         _exit((*built_in[cmd->bui]) (info, index_cmd)); // exiting with cmd exit code
    }
    else
    {
        waitpid(cpid, &status, 0); // waits for child process and returns status
        close(pipefd[1]); // closing useless reading extremity of pipe
        dup2(pipefd[0], STDIN_FILENO); // reading what cmd wrote
        store_output(cmd);
        if (cmd->bui == 2)
            info->crashed = TRUE;
        close(pipefd[0]); // closing last pipe fd
        dup2(saved_stdout, STDOUT_FILENO); // restoring stdout and stdin to original fds
        dup2(saved_stdin, STDIN_FILENO);
        return(EXIT_SUCCESS);
    }
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
