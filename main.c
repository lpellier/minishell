#include "minishell.h"

//char **ft_getbase_env(char *s)
//{
//    int i;
//    char **res;
//
//    i = 0;
//    while (s[i] && s[i] != '=')
//        i++;
//    if (s[i])
//    {
//        if (!(res = (char**)ft_calloc(sizeof(char *), 3)))
//            return (NULL);
//        res[0] = ft_substr(s, 0, i);
//        res[1] = ft_strdup(&s[i +1]);
//        res[2] = NULL;
//        return (res);
//    }
//    return (NULL);
//}
//
//void    ft_begin_env(char **envp, t_info info)
//{
//    int i;
//    char **line;
//
//    i = 0;
//    while (envp[i])
//    {
//        line = ft_getbase_env(envp[i]);
//        if (line != NULL)
//        {
//            ft_add_env(info, line[0], line[1]);
//            safe_free((void **)&line);
//        }
//        i++;
//    }
//}

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

void    shell_loop(char **envp)
{
    t_info info; // info struct : keeps track of various information
    char *cur_dir; // current directory

    // simply assigns each built in function to a number, according to built in index enum
    init_built_in();
//    ft_begin_env(envp, info);
    ft_printf(RED     "Welcome to Minisheh\n"     RESET);
    while (1)
    {
        // gets current directory as string by splitting current path with '/'
        cur_dir = get_cur_dir(&info); 
        ft_printf(BLUE "~ %s > " RESET, cur_dir);
        info.cmd_head = ft_create_elem(create_cmd_struct());
        // reads cmd and stocks it into cmd var
        read_line(&info);
        // ft_printf("---\n%s | %s | %d\n", info.head->cmd, info.head->input, info.head->bui);
        ft_list_clear(info.cmd_head, free_cmd_struct);
    }
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    system("clear");
    shell_loop(envp);
}
