#include "minishell.h"

int		pipe_or_colon(char c)
{
	if (c == '|' || c == ';')
		return (1);
	else if (c == '\0')
		return (-1);
	else
		return (0);
}

int get_input(char *line, t_cmd *cmd)
{
	int index;

	index = 0;
	while (line[index] && !pipe_or_colon(line[index]))
		index++;
	if (!(cmd->input = malloc(sizeof(char) * index + 1)))
		return (-1);
	index = 0;
	while (line[index] && !pipe_or_colon(line[index]))
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
			return (0);
		option++;
	}
	return (1);
}

int get_cmd(char *line, t_cmd *cmd)
{
	char **words;

	words = ft_split(line, ' ');
	if (words[0] && words[1] && words[1][0] == '-')
	{
		cmd->option = ft_strdup(words[1]);
		if (!ft_strncmp(words[0], "echo", 4) && option_only_n(cmd->option))
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
        return (1);
    return (0);
}

#include <string.h>
// recursive function that allows creating as many linked lists as there are commands 
// is there another cmd determined by whether there is a pipe | or a semi-colon ;
void read_cmd(char *line, t_info *info, int index, int index_cmd, char **envp)
{
    t_cmd *cmd;

    // for now cmd is first list in chain
    // should adapt and iterate with index
    cmd = ft_list_at(info->cmd_head, index_cmd)->data;
    while (is_whitespace(line[index]))
        index++;
	index += get_cmd(&line[index], cmd);
    while (is_whitespace(line[index]))
        index++;
	if (cmd->option)
	    index += ft_strlen(cmd->option);
	//printf("%s\n", line + index);
    while (is_whitespace(line[index]))
        index++;
	index += get_input(&line[index], cmd);
    while (is_whitespace(line[index]))
        index++;
	compare_cmd(cmd);
	ft_printf("---\n%s | %s | %s | %d\n", cmd->cmd, cmd->option, cmd->input, cmd->bui);
	if (cmd->bui == 9 || cmd->bui == 8)
		ft_printf("Invalid command bitch\n");
	else
		(*built_in[cmd->bui]) (cmd, envp);
    while (is_whitespace(line[index]))
        index++;
	ft_printf("---\n");
	if (pipe_or_colon(line[index]) == 1)
	{
        ft_list_push_back(&info->cmd_head, create_cmd_struct());
        read_cmd(line, info, index + 1, index_cmd + 1, envp);
    }
}

// reads line using gnl and feeds t_cmd linked lists
void read_line(t_info *info, char **envp)
{
	char *line;

	get_next_line(0, &line);
	read_cmd(line, info, 0, 0, envp);
	if (line)
	    free(line);
	line = NULL;
}

// This function will be used to check for executables in directories addressed in $PATH
//int    directories()
//{
//    DIR *d;
//    struct dirent *dir;
//    d = opendir(".");
//    if (d)
//    {
//        while ((dir = readdir(d)) != NULL)
//        {
//            printf("%s\n", dir->d_name);
//        }
//        closedir(d);
//    }
//
//    return(0);
//}

char *get_cur_dir(t_info *info)
{
    int i;
    char **split;

    i = 0;
    getcwd(info->cur_path, sizeof(info->cur_path));
    split = ft_split(info->cur_path, '/');
    while (split[i])
        i++;
    return split[i - 1];
}
