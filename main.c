#include "minishell.h"

void    shell_loop()
{
    enum built_in_index bui; // bui -> built-in index : keeps track of cmd calls
    t_info info; // info struct : keeps track of various information
    int crashed; // tells program when to stop
    char *cmd; // what is being written by user
    char **separated; // cmd separated by words, separated using ' ' 
    char *cur_dir; // current directory

    // simply assigns each built in function to a number, according to built in index enum
    init_built_in(); 
    crashed = FALSE;
    ft_printf(RED     "Welcome to Minisheh\n"     RESET);
    while (!crashed)
    {
        reset_info(&info);
        // gets current directory as string by splitting current path with '/'
        cur_dir = get_cur_dir(&info); 
        // resets cmd
        cmd = NULL; 
        ft_printf(BLUE "~ %s > " RESET, cur_dir);
        // reads cmd and stocks it into cmd var
        get_next_line(0, &cmd); 
        separated = ft_split(cmd, ' ');
        if (separated[0] && separated[1] && !(ft_strncmp(separated[1], "-n", 2)))
        {
            info.option = 1;
            separated[0] = ft_strjoin(separated[0], separated[1]);
        }
        // reads cmd and assigns bui right number if cmd exists
        compare_cmd(separated[0], &bui);
        if (bui == 8)
            ft_printf("Invalid command bitch\n");
        else
            (*built_in[bui]) (cmd, &info);
        free_everything(&info, separated, cmd);
    }    
}

int main()
{
    system("clear");
    shell_loop();
}