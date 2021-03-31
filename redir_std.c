/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_std.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:24:27 by tefroiss          #+#    #+#             */
/*   Updated: 2021/03/30 20:50:51 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ATTENTION, STRCHR CONTIENT UN TERNAIRE

int		ft_checkc(char c, const char *set)
{
    while (*set)
    {
        if (c == *set)
            return (1);
        set++;
    }
    return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
    int		i;
    int		j;

    if (s1 != NULL && set != NULL)
    {
        i = 0;
        while (ft_checkc(s1[i], set))
            i++;
        j = (ft_strlen(s1));
        while (ft_checkc(s1[j - 1], set) && j > 1)
            j--;
        if (j == 1)
            return (ft_strdup("\0"));
        return (ft_substr(s1, i, (j - i)));
    }
    return (ft_strdup("\0"));
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (count != 0 && size != 0)
	{
		if (!(mem = malloc(count * size)))
			return (NULL);
		ft_bzero(mem, count * size);
		return (mem);
	}
	return (malloc(1));
}

char *ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (src[i] != '\0' && (i < n))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_isseparator(int c)
{
	return (ft_cinset(c, SEPARATOR));
}

int	ft_cinset(const char c, const char *set)
{
	int i;

	if (set != NULL)
	{
		i = 0;
		while (set[i])
		{
			if (c == set[i])
				return (1);
			i++;
		}
		return (0);
	}
	return (-1);
}

int	ft_isspace(int c)
{
	return (ft_cinset(c, "\t\n\r\v\f "));
}

void what_is_the_sep(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>')
		{
			if (line[i + 1] && line[i + 1] == '>')
			{
				info.nb_rd_redir--;
				return;
			}
			else
			{
				info.nb_r_redir--;
				return;
			}
		}
 		i++;
	}
}

char *create_empty_file(char *str)
{
	int i;
	char *s;
	char *file;
	char *tmp;
	int j;

	i = 0;
	j = ft_strlen(str);
	while ((info.nb_r_redir > 1 || info.nb_rd_redir > 1) || (info.nb_r_redir == 1 && info.nb_rd_redir == 1))
	{
		what_is_the_sep(str);
		s = ft_strdup(get_file(str));
		while (s[i] != '\0' && !ft_isspace(s[i]))
			i++;
		if (!(file = (char *)ft_calloc(i, sizeof(char))))
			return (NULL);
		file = ft_strncpy(file, s, i);
		open(file, O_WRONLY | O_CREAT, 00644);
		if (!(tmp = (char *)ft_calloc(j - i + 1, sizeof(char))))
			return (NULL);
		i = 0;
		j = 0;
		while (str[i] != '\0' && !ft_isseparator(str[i]))
		{
			tmp[j] = str[i];
			i++;
			j++;
		}
		while (str[i] != '\0' && (ft_isseparator(str[i]) || ft_isspace(str[i])))
			i++;
		i = i + ft_strlen(file) + 1;
		while (str[i] != '\0')
		{
			tmp[j] = str[i];
			i++;
			j++;
		}
		tmp[j] = '\0';
		// ft_printf("tmp = %s\n", tmp);
		create_empty_file(tmp);
	}
	// ft_printf("%d && %d\n", info.nb_r_redir, info.nb_rd_redir);
	// ft_printf("str = %s\n", str);
	return (tmp);
}

char *get_file(char *s)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && !ft_isseparator(s[i]))
		i++;
    while (s[i] != '\0' && ft_isseparator(s[i]))
        i++;
	while (ft_isspace(s[i]))
		i++;
	k = i;
	while (s[i] != '\0')
	{
		i++;
		j++;
	}
	return(ft_substr(s, k, j));
}

void redir_stdout(t_cmd *cmd)
{
	char *str;
	char *s;
	char *file;
	int i;
	int j;

	str = ft_strdup(cmd->input);
	i = 0;
	if ((info.nb_r_redir > 1 || info.nb_rd_redir > 1) || (info.nb_r_redir == 1 && info.nb_rd_redir == 1))
		str = ft_strdup(create_empty_file(str));
	while (str[i] && !ft_isseparator(str[i]))
		i++;
	j = i;
	i = 0;
	while (str[i])
		i++;
	if (!(s = (char *)ft_calloc(i, sizeof(char))))
		return ;
	file = ft_strdup(get_file(ft_strncpy(s, str, i)));
	// ft_printf("%s\n", file);
	if (!(s = (char *)ft_calloc(j, sizeof(char))))
		return ;
	s = ft_strncpy(s, str, j);
	s = ft_strtrim(s, " ");
	if (info.nb_r_redir == 1)
		info.file_fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 00644);
	else if (info.nb_rd_redir == 1)
		info.file_fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 00644);
	ft_putstr_fd(s, info.file_fd);
	close(info.file_fd);
}

void ft_symbol(t_cmd *cmd)
{ 
	// if (info.nb_l_redir == 1)
	// 	redir_stdin();
	if (info.nb_r_redir > 0 || info.nb_rd_redir > 0)
		redir_stdout(cmd);
}
