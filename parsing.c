#include "minishell.h"

int		pipe_or_colon(char c)
{
	if (c == '|' || c == ';')
		return (SUCCESS);
	else if (c == '\0')
		return (OTHER);
	else
		return (FAILURE);
}

int get_input(char *line, t_cmd *cmd)
{
	int index;

	index = 0;
	while (line[index] && pipe_or_colon(line[index]))
		index++;
	if (!(cmd->input = malloc(sizeof(char) * index + 1)))
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

int option_only_n(char *option)
{
	option += 1;
	while (*option)
	{
		if (*option != 'n')
			return (FAILURE);
		option++;
	}
	return (SUCCESS);
}

int get_cmd(char *line, t_cmd *cmd)
{
	char **words;

	words = ft_split(line, ' ');
	if (words[0] && words[1] && words[1][0] == '-')
	{
		cmd->option = ft_strdup(words[1]);
		if (!compare_size(words[0], "echo") && !option_only_n(cmd->option))
			cmd->cmd = ft_strdup(words[0]);
	}
	else if (words[0])
		cmd->cmd = ft_strdup(words[0]);
	free_tab(words);
	return (ft_strlen(cmd->cmd));
}

int is_whitespace(char c)
{
    if (c == 32 || (c >= 9 && c <= 13))
        return (SUCCESS);
    return (FAILURE);
}

int spaces(char *s)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (!is_whitespace(s[i++]))
        count++;
    return (count);
}

void test(t_cmd *cmd)
{
    ft_printf(CYAN"%s"RESET, cmd->cmd);
    ft_printf(RED" | "RESET);
    ft_printf(CYAN"%s"RESET, cmd->option);
    ft_printf(RED" | "RESET);
    ft_printf(CYAN"%s"RESET, cmd->input);
    ft_printf(RED" | bui -> "RESET);
    ft_printf(CYAN"%d\n"RESET, cmd->bui);
}

// recursive function that allows creating as many linked lists as there are commands 
// is there another cmd determined by whether there is a pipe | or a semi-colon ;
void read_cmd(char *line, t_info *info, int index, int index_cmd)
{
    t_cmd *cmd;

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
	if (cmd->output && !cmd->input)
    {
	    cmd->input = ft_strdup(cmd->output);
        free(cmd->output);
        cmd->output = NULL;
    }
    test(cmd);
    if (cmd->cmd && cmd->bui == 9)
        cmd->output = ft_strjoin(ft_strjoin("minisheh: ", cmd->cmd), ": command not found\n");
    else if (cmd->bui == 8)
        pipe_for_exec(info, index_cmd); // this should only apply to non-built-ins. so bui = 8
    else if (!cmd->cmd)
        cmd->output = ft_strdup("");
    else
        (*built_in[cmd->bui]) (info, index_cmd);

    index += spaces(&line[index]);
	if (!pipe_or_colon(line[index]))
	{
        ft_list_push_back(&info->cmd_head, create_cmd_struct());
        read_cmd(line, info, index + 1, index_cmd + 1);
    }
	if (cmd->output)
	    ft_printf("%s", cmd->output);
}

// reads line using gnl and feeds t_cmd linked lists
void read_line(t_info *info)
{
	char *line;

	get_next_line(0, &line);
	read_cmd(line, info, 0, 0);
	if (line)
	    free(line);
	line = NULL;
}

// This function will be used to check for executables in directories addressed in $PATH
int    directories(char *path, char *cmd)
{
    DIR *d;
    struct dirent *dir;
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

char *get_cur_dir(t_info *info)
{
    int i;
    char **split;
    char *res;

    i = 0;
    getcwd(info->cur_path, sizeof(info->cur_path));
    split = ft_split(info->cur_path, '/');
    while (split[i])
        i++;
    if (i == 0)
    	res = NULL;
    else
    	res = ft_strdup(split[i - 1]);
	free(split);
    return (res);
}
