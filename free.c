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
	ft_list_clear(info->head);
	return (1);
}

void	free_cmd(t_cmd *list)
{
	if (list->cmd)
		free(list->cmd);
	list->cmd = NULL;
	if (list->input)
		free(list->input);
	list->input = NULL;
	list->bui = 0;
	if (list->option)
		free(list->option);
	list->option = NULL;
}

void	ft_list_clear(t_cmd *begin_list)
{
	t_cmd	*ptr;

	while (begin_list)
	{
		ptr = begin_list->next;
		free_cmd(begin_list);
		free(begin_list);
		begin_list = ptr;
	}
	begin_list = 0;
}

// void    free_everything(t_info *info, char **tab, char *cmd)
// {
//     free_tab(tab);
// }
