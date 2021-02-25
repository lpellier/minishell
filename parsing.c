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

	index = 1;
	while (line[index] && !pipe_or_colon(line[index]))
		index++;
	if (!(cmd->input = malloc(sizeof(char) * index)))
		return (-1);
	index = 1;
	while (line[index] && pipe_or_colon(line[index]) == 0)
	{
		cmd->input[index -1] = line[index];
		index++;
	}
	return (ft_strlen(cmd->input));
	return (0);
}

char	*how_many_spaces(char *line)
{
	int i;
	char *spaces;

	i = 0;
	while (*line && *line == ' ')
		line++;
	while (*line && *line != ' ')
		line++;
	while (*line && *line == ' ')
	{
		line++;
		i++;
	}
	if (!(spaces = malloc(sizeof(char) * i + 1)))
		return (NULL);
	while (i)
	{
		*spaces = ' ';
		i--;
	}
	return (spaces);
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
	char *spaces;
	char **words;

	words = ft_split(line, ' ');
	spaces = how_many_spaces(line);
	if (words[0] && words[1] && words[1][0] == '-')
	{
		cmd->option = ft_strdup(words[1]);
		if (!ft_strncmp(words[0], "echo", 4) && option_only_n(cmd->option))
			cmd->cmd = ft_strjoin(ft_strjoin(words[0], spaces), cmd->option);
		else
			cmd->cmd = ft_strdup(words[0]);
	}
	else if (words[0])
	{
		cmd->cmd = ft_strdup(words[0]);
	}
	free_tab(words);
	return (ft_strlen(cmd->cmd));
}

#include <string.h>
// recursive function that allows creating as many linked lists as there are commands 
// is there another cmd determined by whether there is a pipe | or a semi-colon ;
void read_cmd(char *line, t_cmd *cmd)
{
	int index;

	index = get_cmd(line, cmd);
	if (*line)
		line = ft_strnstr(line, cmd->cmd, ft_strlen(line));
	if (*line)
	{	
		index = get_input(line, cmd);
		line = ft_strnstr(line, cmd->input, ft_strlen(line)) + index;
	}
	compare_cmd(cmd);
	if (cmd->bui == 9)
		ft_printf("Invalid command bitch\n");
	else
		(*built_in[cmd->bui]) (cmd);
	if (pipe_or_colon(*line) == 1)
	{
		ft_list_push_back(&cmd, NULL, NULL, 0, 0);
		read_cmd(line, cmd->next);
	}
}

// reads line using gnl and feeds t_cmd linked lists
void read_line(t_info *info)
{
	char *line;
	char **separated;

	get_next_line(0, &line); 
	// separated = ft_split(line, ' ');
	read_cmd(line, info->head);
	// if (separated[0] && separated[1] && !(ft_strncmp(separated[1], "-n", 2)))
	// 	separated[0] = ft_strjoin(separated[0], separated[1]);
	// reads cmd and assigns bui right number if cmd exists
	// compare_cmd(separated[0], &bui);
}

// This function will be used to check for executables in directories addressed in $PATH
int    directories()
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }

    return(0);
}

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