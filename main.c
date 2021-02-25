#include "minishell.h"

void    shell_loop()
{
    t_info info; // info struct : keeps track of various information
    int crashed; // tells program when to stop 
    char *cur_dir; // current directory

    // simply assigns each built in function to a number, according to built in index enum
    init_built_in(); 
    info.crashed = FALSE;
    ft_printf(RED     "Welcome to Minisheh\n"     RESET);
    while (!info.crashed)
    {
        // gets current directory as string by splitting current path with '/'
        cur_dir = get_cur_dir(&info); 
        ft_printf(BLUE "~ %s > " RESET, cur_dir);
        info.head = ft_create_elem(NULL, NULL, 0, NULL);
        // reads cmd and stocks it into cmd var
        read_line(&info);
        // info.crashed = TRUE;
        // reset_info(&info);
    }
}

int main()
{
    system("clear");
    shell_loop();
}