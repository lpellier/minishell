//
// Created by Téo Froissart on 02/03/2021.
//

#include "minishell.h"

//void		ft_sigquit(int sig);
//
//void	ft_sigint(int sig);

void	ft_sigterm(int sig, t_info *info)
{
    (void)sig;
    info->crashed = TRUE;
}
