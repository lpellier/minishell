/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaspellier <lucaspellier@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 10:49:49 by lpellier          #+#    #+#             */
/*   Updated: 2020/03/25 21:07:04 by lucaspellie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*line_def(char *stock, int i)
{
	char	*new;
	int		len;

	if (stock == NULL)
		return (ft_strdup("\0"));
	len = ft_strlen(stock);
	if (i == -1)
		new = ft_substr(stock, 0, len);
	else
		new = ft_substr(stock, 0, i);
	return (new);
}

char	*update_stock(char *stock, int i)
{
	char	*temp;
	int		len;

	len = ft_strlen(stock);
	if (i == -1)
		i++;
	temp = ft_substr(stock, i + 1, len);
	free(stock);
	stock = temp;
	return (stock);
}

char	*init_stock(char *stock, char *buf)
{
	char *temp;

	if (stock == NULL)
		stock = ft_strdup(buf);
	else
	{
		temp = ft_strjoin(stock, buf);
		free(stock);
		stock = temp;
	}
	return (stock);
}

int		append_and_update(char **stock, char **line)
{
	int i;

	if ((i = check_n(*stock)) > 0)
	{
		*line = line_def(*stock, i - 1);
		*stock = update_stock(*stock, i - 1);
		return (i);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	int			i;
	static char	*stock = NULL;
	char		buf[BUFFER_SIZE + 1];

	if (!(fd >= 0 && BUFFER_SIZE > 0 && line != NULL && !read(fd, buf, 0)))
		return (-1);
	while ((ret = read(fd, buf, BUFFER_SIZE)))
	{
		buf[ret] = '\0';
		stock = init_stock(stock, buf);
		if ((i = append_and_update(&stock, line)))
			return (1);
	}
	if ((i = append_and_update(&stock, line)))
		return (1);
	*line = line_def(stock, i - 1);
	free(stock);
	stock = NULL;
	return (0);
}
