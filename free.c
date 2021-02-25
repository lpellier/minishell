#include "minishell.h"

void    free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        tab[i] = NULL;
    }
}

// void    free_everything(t_info *info, char **tab, char *cmd)
// {
//     free_tab(tab);
// }