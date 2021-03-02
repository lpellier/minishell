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

void	free_cmd_struct(void *data)
{
    t_cmd *ptr;

    ptr = (t_cmd *)data;
    ptr->bui = 9;
    if (ptr->cmd)
        free(ptr->cmd);
    ptr->cmd = NULL;
    if (ptr->input)
        free(ptr->input);
    ptr->input = NULL;
    if (ptr->option)
        free(ptr->option);
    ptr->option = NULL;
    if (ptr->output)
        free(ptr->output);
    ptr->output = NULL;
}

void	free_env_struct(void *data)
{
    t_env *ptr;

    ptr = (t_env *)data;
    if (ptr->value)
        free(ptr->value);
    ptr->value = NULL;
    if (ptr->key)
        free(ptr->key);
    ptr->key = NULL;
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
