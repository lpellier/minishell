#include "minishell.h"

void    free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        tab[i] = NULL;
        free(tab[i]);
    }
}

void    free_everything(t_info *info, char **tab, char *cmd)
{
    free_tab(tab);
    info->input = NULL;
    free(info->input);
    *cmd = NULL;
    free(cmd);
}