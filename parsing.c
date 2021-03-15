/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:24:47 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/15 13:28:42 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			pipe_or_colon(char c)
{
	if (c == '|' || c == ';')
		return (SUCCESS);
	else if (c == '\0')
		return (OTHER);
	else
		return (FAILURE);
}

int			get_input(char *line, t_cmd *cmd)
{
	int		index;

	index = 0;
	while (line[index] && pipe_or_colon(line[index]))
		index++;
	if (!(cmd->input = malloc(sizeof(char) * (index + 1))))
		return (FAILURE);
	index = 0;
	while (line[index] && pipe_or_colon(line[index]))
	{
		cmd->input[index] = line[index];
		index++;
	}
	cmd->input[index] = '\0';
	if (cmd->input[0] == '\0')
		cmd->input = NULL;
	return (ft_strlen(cmd->input));
}

int			get_cmd(char *line, t_cmd *cmd)
{
	char	**words;

	words = ft_split(line, " ");
	if (words[0] && words[1] && words[1][0] == '-')
		cmd->option = ft_strdup(words[1]);
	if (words[0])
		cmd->cmd = ft_strdup(words[0]);
	free_tab(words);
	return (ft_strlen(cmd->cmd));
}

int			is_whitespace(char c)
{
    if (c == 32 || (c >= 9 && c <= 13))
        return (SUCCESS);
    return (FAILURE);
}

int			spaces(char *s)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i] && !is_whitespace(s[i]))
	{
		count++;
		i++;
	}
	return (count);
}

void		test(t_cmd *cmd)
{
	ft_printf(CYAN "'%s'" RESET, cmd->cmd);
	ft_printf(RED " | " RESET);
	ft_printf(CYAN "'%s'" RESET, cmd->option);
	ft_printf(RED " | " RESET);
	ft_printf(CYAN "'%s'" RESET, cmd->input);
	ft_printf(RED " | bui -> " RESET);
	ft_printf(CYAN "%d\n" RESET, cmd->bui);
}

/*
** recursive function that allows creating as many
** linked lists as there are commands
** is there another cmd determined by whether there is a pipe |
** or a semi-colon for now;
*/

void		read_cmd(char *line, t_info *info, int index, int index_cmd)
{
	t_cmd	*cmd;

	cmd = ft_list_at(info->cmd_head, index_cmd)->data;
	index += spaces(&line[index]);
	index += get_cmd(&line[index], cmd);
	index += spaces(&line[index]);
	if (cmd->option)
		index += ft_strlen(cmd->option);
	index += spaces(&line[index]);
	index += get_input(&line[index], cmd);
	index += spaces(&line[index]);
	compare_cmd(info, cmd);
	test(cmd);
	if (cmd->cmd && cmd->bui == 9)
		info->output = ft_strjoin(ft_strjoin("minisheh: ", cmd->cmd),
			": command not found\n");
	else if (cmd->bui == 9)
		info->output = ft_strdup(""); /* might cause an issue later */
	else if (!pipe_or_colon(line[index]))
		pipe_for_exec(info, index_cmd, line, index, 1);
	else if (pipe_or_colon(line[index]) && cmd->bui == 8)
		pipe_for_exec(info, index_cmd, line, index, 0);
	else
		info->cmd_status = (*built_in[cmd->bui])(info, index_cmd);
}

/*
** replaces every $ with its env variable counterpart
** need to replace lib functions with libft ones
*/

#include <string.h>

// You must free the result if result is non-NULL.
char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}


char *replace_dollars_env(t_info *info, char *line)
{
	char *test;
	char *dst;
	t_list *value;
	char *cmp;
	int i;

	test = ft_strdup(line);
	while ((test = strstr(test, "$")))
	{
		if (test[1] && is_whitespace(test[1]) && test[1] != '$')
		{
			i = 1;
			while (test[i] && is_whitespace(test[i]) && test[i] != '$')
				i++;
			if (!(dst = malloc(sizeof(char) * i)))
				return (NULL);
			strncpy(dst, test, i);
			dst[i] = '\0';
			value = (ft_list_find(info->env_head,
				create_env_struct(dst + 1, "NULL"), cmp_env));
			if (value && (cmp = ft_strdup(((t_env *)value->data)->value)))
			{
			    line = str_replace(line, dst, cmp);
			    free(cmp);
			 	cmp = NULL;
			}
		}
		test++;
	}
	return (line);
}

/* reads line using gnl and feeds t_cmd linked lists */

void		read_line(t_info *info, int first)
{
	char	*line;
	char	*true_line;

	get_next_line(0, &line);
	if (first)
		info->history_head = ft_create_elem(create_history_struct(ft_strdup(line)));
	else
    	ft_list_push_front(&info->history_head, create_history_struct(ft_strdup(line)));
	true_line = replace_dollars_env(info, line);
	read_cmd(true_line, info, 0, 0);
	if (line)
		free(line);
	line = NULL;
	if (info->output)
	{
		ft_printf("%s", info->output);
		free(info->output);
	}
	info->output = NULL;
}

/*
** This function will be used to check for executables
** in directories addressed in $PATH
*/

int			directories(char *path, char *cmd)
{
	DIR				*d;
	struct dirent	*dir;

	d = opendir(path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
			if (!compare_size(cmd, dir->d_name))
				return (SUCCESS);
		closedir(d);
	}
	return (FAILURE);
}

char		*get_cur_dir(t_info *info)
{
	int		i;
	char	**split;
	char	*res;

	i = 0;
	getcwd(info->cur_path, sizeof(info->cur_path));
	split = ft_split(info->cur_path, "/");
	while (split[i])
		i++;
	if (i == 0)
		res = NULL;
	else
		res = ft_strdup(split[i - 1]);
	free_tab(split);
	return (res);
}
