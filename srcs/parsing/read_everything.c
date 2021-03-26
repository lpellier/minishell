/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:17:51 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/25 16:39:37 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		custom_strncat(char *dest, char *src, int nb)
{
	int	i;
	int	j;
	
	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0' && j < nb)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
}

void		custom_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char 	*read_everything()
{
	char	key;
	char	*line;
	int		index;

	key = 0;
	index = 0;
	line = ft_calloc(4096, sizeof(char));
	ft_bzero(line, 4096);
	while (key != '\n')
	{
		get_pos(&info.cursor.posx, &info.cursor.posy);
		if (read(0, &key, 1) == -1)
			return (NULL);
// 		if (key == 27)
// 		{
// 			tmp = ft_strdup(line);
// 			ft_bzero(line, 4096)
// ;			check_for_arrows(&line, &index);
// 		}
// 		else if (key == 127)
// 		{
// 			tmp = ft_strdup(line);
// 			ft_bzero(line, 4096);
// 			delete_char(&line, tmp, index);
// 			index--;
// 		}
		if (key != '\n')
		{
			write(STDOUT_FILENO, &key, 1);
			//custom_strncat(line, &key, 1);
			index++;
		}
	}
	return (line);
}

/* reads line using gnl and feeds t_cmd linked lists */

void		read_line(int first)
{
	char *line;
	(void) first;
	// char	*true_line;

	// if (first)
	// 	info.history_head = ft_create_elem(create_history_struct(NULL));
	// else
    // 	ft_list_push_front(&info.history_head, create_history_struct(NULL));
	line = read_everything();
	custom_strcpy(line, "exit");
	// true_line = replace_dollars_env(ft_strdup(line));
	read_cmd(line, 0, 0);
	if (line)
		free(line);
	line = NULL;
	// if (true_line)
	// 	free(true_line);
	// true_line = NULL;
	if (info.output)
	{
		ft_printf("%s", info.output);
		free(info.output);
	}
	info.output = NULL;
}
