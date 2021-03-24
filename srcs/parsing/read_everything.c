/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:17:51 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/24 18:05:01 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_charjoin(const char *s, char c)
{
	char	*res;
	int		i;

	i = 0;
	if (s == NULL || c == '\0')
		return (NULL);
	if (!(res = malloc(sizeof(char) * ft_strlen(s) + 2)))
		return (NULL);
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = '\0';
	return (res);
}

char 	*read_everything()
{
	char	c;
	char	*ret;
	char	*tmp;
	int		index;

	c = 0;
	index = 0;
	ret = ft_strdup("");
	while (c != '\n')
	{
		tmp = ft_strdup("");
		get_pos(&info.cursor.posx, &info.cursor.posy);
		if (read(0, &c, 1) == -1)
			return (NULL);
		if (c == 27)
		{
			if (!(ret = check_for_arrows(index)))
				ret = ft_strdup("");
		}
		else if (c == 127)
		{
			ret = delete_char(ret, index);
			index--;
		}
		else if (c != '\n')
		{
			write(STDOUT_FILENO, &c, 1);
			free(tmp);
			tmp = ft_strdup(ret);
			free(ret);
			ret = ft_charjoin(tmp, c);
			if (((t_history *)info.history_head->data)->line)
				free(((t_history *)info.history_head->data)->line);
			((t_history *)info.history_head->data)->line = ft_strdup(ret);
			index++;
		}
	}
	if (((t_history *)info.history_head->data)->line)
		free(((t_history *)info.history_head->data)->line);
	((t_history *)info.history_head->data)->line = ft_strdup(ret);
	free(tmp);
	return (ret);
}

/* reads line using gnl and feeds t_cmd linked lists */

void		read_line(int first)
{
	char *line;
	char	*true_line;

	if (first)
		info.history_head = ft_create_elem(create_history_struct(NULL));
	else
    	ft_list_push_front(&info.history_head, create_history_struct(NULL));
	line = read_everything();
	true_line = replace_dollars_env(ft_strdup(line));
	read_cmd(true_line, 0, 0);
	if (line)
		free(line);
	line = NULL;
	if (true_line)
		free(true_line);
	true_line = NULL;
	if (info.output)
	{
		ft_printf("%s", info.output);
		free(info.output);
	}
	info.output = NULL;
}
