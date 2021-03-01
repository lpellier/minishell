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
        free(cur_dir);
    }
    ft_list_clear(info.env_head, free_env_struct);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    system("clear");
    shell_loop(envp);
}
