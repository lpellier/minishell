#include "minishell.h"

void init(t_info *info, char **envp)
{
    // simply assigns each built in function to a number, according to built in index enum
    init_built_in();
    info->crashed = FALSE;
    info->output = NULL;
    info->env_head = ft_create_elem(create_env_struct(NULL, NULL));
    init_env(info, envp);
    info->dir_paths = ft_split(((t_env *)ft_list_find(info->env_head, \
    create_env_struct("PATH", "NULL"), cmp_env)->data)->value, ":");
}

int    shell_loop(char **envp)
{
    t_info info; // info struct : keeps track of various information
    char *cur_dir; // current directory

    init(&info, envp);
    ft_printf(RED     "Welcome to Minisheh\n"     RESET);
    while (!info.crashed)
    {
        // gets current directory as string by splitting current path with '/'
        if (!(cur_dir = get_cur_dir(&info)))
            cur_dir = ft_strdup("/");
        ft_printf(BLUE "~ %s > " RESET, cur_dir);
        info.cmd_head = ft_create_elem(create_cmd_struct());
        // reads cmd and stocks it into cmd var
        read_line(&info);
        ft_list_clear(info.cmd_head, free_cmd_struct);
        ft_bzero(info.cur_path, 4096);
//        signal(SIGQUIT, ft_sigquit); // ctrl + \
//        signal(SIGINT, ft_sigint); // ctrl + c
        signal(SIGTERM, (void (*)(int)) ft_sigterm); // ctrl + d
        free(cur_dir);
    }
    free_tab(info.dir_paths);
    ft_list_clear(info.env_head, free_env_struct);
    return (SUCCESS);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    system("clear");
    exit(shell_loop(envp));
}
