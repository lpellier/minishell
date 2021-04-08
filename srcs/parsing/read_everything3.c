/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_everything3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:33:29 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/08 16:34:08 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalpha_ordollar(int c)
{
	if (c == '?' || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

// bslashes within a dquote only work if the following character is a dollar, 
// a dquote,(a backquote) or another bslash
// not sure whether backquotes should be supported or not 

// other warning : when used solo, a backslash lets you finish a 
// command in line under current one. 
// should i implement this ?

int	dollar(char *line, int *index)
{
	char	*var;
	t_list	*var_list;
	t_env	*var_key;
	int		i;

	i = 0;
	if (!line[*index] || !line[*index + 1] || (line[*index + 1] && \
		!ft_isalpha_ordollar(line[*index + 1])))
	{
		*index += 1;
		return (FAILURE);
	}
	if (ft_calloc((void **)&var, 256, sizeof(char)))
		return (FAILURE);
	while (line[*index] && (ft_isalpha(line[*index]) || (line[*index] \
		== DOLLAR && i == 0) || (line[*index] == '?')))
	{
		if (i > 0)
			var[i - 1] = line[*index];
		remove_char(line, *index);
		i++;
	}
	var_list = ft_list_find(g_info.env_head, \
		create_env_struct(var, NULL), cmp_env);
	if (var_list)
	{
		var_key = (t_env *)var_list->data;
		i = 0;
		while (var_key->value[i])
		{
			add_char(line, var_key->value[i], *index);
			*index += 1;
			i++;
		}
	}
	return (SUCCESS);
}
