#include "minishell.h"

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
    {
        i++;
    }
    return split[i - 1];
}