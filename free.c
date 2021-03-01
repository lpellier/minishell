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

int    reset_info(t_info *info)
{
	ft_list_clear(info->cmd_head, free_cmd_struct);
	return (1);
}

void	free_cmd_struct(void *data)
{
    t_cmd *test;

    test = (t_cmd *)data;
    test->bui = 9;
    if (test->cmd)
        free(test->cmd);
    test->cmd = NULL;
    if (test->input)
        free(test->input);
    test->input = NULL;
    if (test->option)
        free(test->option);
    test->option = NULL;
    if (test->output)
        free(test->output);
    test->output = NULL;
}

void	ft_list_clear(t_list *begin_list, void (*free_fct)(void *))
{
    t_list	*ptr;

    while (begin_list)
    {
        ptr = begin_list->next;
        free_fct(begin_list->data);
        free(begin_list);
        begin_list = ptr;
    }
    begin_list = NULL;
}

// void    free_everything(t_info *info, char **tab, char *cmd)
// {
//     free_tab(tab);
// }
