#include "minishell.h"

int     init_env(t_info *info, char **envp)
{
    int i;
    char **key_value;

    i = 0;
    while (envp[i])
    {
        key_value = ft_split(envp[i], '=');
        ft_list_push_back(&info->env_head, create_env_struct(key_value[0], key_value[1]));
        free(key_value);
        i++;
    }
    return (0);
    // might wanna start adding actual error codes in functions
}

// mallocs and creates cmd struct, returns pointer on struct
t_cmd   *create_cmd_struct()
{
    t_cmd *cmd;

    if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
        return NULL;
    cmd->bui = 9;
    cmd->cmd = NULL;
    cmd->input = NULL;
    cmd->option = NULL;
    cmd->output = NULL;
    return (cmd);
}

// same as above for env struct
t_env   *create_env_struct(char *key, char *value)
{
    t_env *env;

    if (!(env = (t_env *)malloc(sizeof(t_env))))
        return NULL;
    env->value = value;
    env->key = key;
    return (env);
}

void    shell_loop(char **envp)
{
    t_info info; // info struct : keeps track of various information
    char *cur_dir; // current directory

    // simply assigns each built in function to a number, according to built in index enum
    init_built_in();
    info.crashed = FALSE;
    info.env_head = ft_create_elem(create_env_struct(NULL, NULL));
    init_env(&info, envp);
    ft_printf(RED     "Welcome to Minisheh\n"     RESET);
    // need to remove infinite loop by adding crashed int to info struct
    // so that i can free env linked list
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
}

char	*ft_move_until(char *str)
{
    if (str)
    {
        while (*str && ft_isalpha(*str))
            str++;
        str++;
    }
    return (str);
}

char	*ft_get_path(char **envp)
{
    char	*line;
    char    **tab;
    int i;

    i = 0;
    // parcours tant que tu trouves pas PATH
    while (ft_strncmp(envp[i], "PATH", 4))
        i++;
    // clone la ligne PATH dans line en enlevant PATH=
    line = ft_strdup(ft_move_until(envp[i]));
    tab = ft_split(line, ':');
    ft_printf("%s", tab[0]);
    free(line);
    return("coucou");
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    ft_get_path(envp);
    system("clear");
    shell_loop(envp);
}
