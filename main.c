#include "minishell.h"

void    shell_loop()
{
    t_info info; // info struct : keeps track of various information
    char *cur_dir; // current directory

    // simply assigns each built in function to a number, according to built in index enum
    init_built_in();
    ft_printf(RED     "Welcome to Minisheh\n"     RESET);
    while (1)
    {
        // gets current directory as string by splitting current path with '/'
        cur_dir = get_cur_dir(&info); 
        ft_printf(BLUE "~ %s > " RESET, cur_dir);
        info.head = ft_create_elem(NULL, NULL, 9, NULL);
        // reads cmd and stocks it into cmd var
        read_line(&info);
        ft_printf("---\n%s | %s | %d\n", info.head->cmd, info.head->input, info.head->bui);
        reset_info(&info);
    }
}

int main()
{
    system("clear");
    shell_loop();
}