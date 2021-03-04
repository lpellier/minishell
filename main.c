#include "minishell.h"

char	*ft_move_until(char *str)
{
    if (str)
    {
        // deplace le pointeur si str existe et si le char est alpha
        while (*str && ft_isalpha(*str))
            str++;
        // passe un char de place, le =
        str++;
    }
    return (str);
}

void	ft_get_path(char **envp, t_info *info)
{
    char	*line;
    int i;

    i = 0;
    // parcours tant que tu trouves pas PATH
    while (ft_strncmp(envp[i], "PATH", 4))
        i++;
    // clone la ligne PATH dans line en enlevant PATH=
    line = ft_strdup(ft_move_until(envp[i]));
    // recupere dans un tableau les differents dossier
    info->tab = ft_split(line, ':');
    free(line);
}

int    shell_loop(char **envp)
{
    t_info info; // info struct : keeps track of various information
    char *cur_dir; // current directory

    // simply assigns each built in function to a number, according to built in index enum
    init_built_in();
    info.crashed = FALSE;
    info.env_head = ft_create_elem(create_env_struct(NULL, NULL));
    init_env(&info, envp);
    ft_get_path(envp, &info);
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
        // ft_printf("---\n%s | %s | %d\n", info.head->cmd, info.head->input, info.head->bui);
        ft_list_clear(info.cmd_head, free_cmd_struct);
        ft_bzero(info.cur_path, 4096);
//        signal(SIGQUIT, ft_sigquit); // ctrl + \
//        signal(SIGINT, ft_sigint); // ctrl + c
        signal(SIGTERM, (void (*)(int)) ft_sigterm); // ctrl + d
        free(cur_dir);
    }
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
