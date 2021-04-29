/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_std.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:24:27 by tefroiss          #+#    #+#             */
/*   Updated: 2021/04/29 13:47:38 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ATTENTION, STRCHR CONTIENT UN TERNAIRE

int	ft_checkc(char c, const char *set)
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

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

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
	int	i;

	if (set != NULL)
	{
		i = 0;
		while (set[i])
		{
			if (c == set[i])
				return (SUCCESS);
			i++;
		}
		return (FAILURE);
	}
	return (OTHER);
}

int	ft_isspace(int c)
{
	return (ft_cinset(c, "\t\n\r\v\f "));
}

int	open_file(t_cmd *cmd, int start, int separator)
{
	int		arg_index;
	int		file_fd;

	file_fd = -1;
	arg_index = sep_in_args(cmd, start) + 1;
	if (separator == R_RIGHT)
		file_fd = open(cmd->args[arg_index], O_WRONLY | O_TRUNC | O_CREAT, 00644);
	else if (separator == R_RIGHTD)
		file_fd = open(cmd->args[arg_index], O_WRONLY | O_APPEND | O_CREAT, 00644);
	else if (separator == R_LEFT)
	{
		file_fd = open(cmd->args[arg_index], O_RDONLY, 00644);
		if (file_fd == -1)
			print_error(NULL, cmd->args[arg_index], \
				"no such file or directory");
	}
	return (file_fd);
}
