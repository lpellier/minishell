#include "libft/libft.h"
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#define PATH_MAX 4096
#define TRUE 1
#define FALSE 0
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

enum built_in_index {
    ECHO,
    ECHO_N,
    EXIT,
    PWD,
    EXPORT,
    UNSET,
    ENV,
    CD,
    NONEXISTENT
};

typedef struct s_info
{
    char cur_path[PATH_MAX];
    int option;
}               t_info;

int ft_echo (char *cmd, t_info *info)
{
    ft_printf("%s\n", cmd);
    return (0);
}

int ft_echo_n (char *cmd, t_info *info)
{
    ft_printf("%s\033[47m\033[30m%%\033[39m\033[49m", cmd);
    return (0);
}

int ft_exit (char *cmd, t_info *info)
{
    exit (0);
}
int ft_pwd (char *cmd, t_info *info)
{
    return (0);
}
int ft_export (char *cmd, t_info *info)
{
    return (0);
}
int ft_unset (char *cmd, t_info *info)
{
    return (0);
}
int ft_env (char *cmd, t_info *info)
{
    return (0);
}
int ft_cd (char *cmd, t_info *info)
{
    chdir(ft_strjoin(info->cur_path, "/.."));
    return (0);
}

int (*built_in[8]) (char *cmd, t_info *info);

void init_built_in()
{
    built_in[0] = ft_echo;
    built_in[1] = ft_echo_n;
    built_in[2] = ft_exit;
    built_in[3] = ft_pwd;
    built_in[4] = ft_export;
    built_in[5] = ft_unset;
    built_in[6] = ft_env;
    built_in[7] = ft_cd;
}

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

void    compare_cmd(char *cmd, enum built_in_index *bui)
{
    if (!(ft_strncmp(cmd, "echo-n", 6)))
        *bui = ECHO_N;
    else if (!(ft_strncmp(cmd, "echo", 4)))
        *bui = ECHO;
    else if (!(ft_strncmp(cmd, "exit", 4)))
        *bui = EXIT;
    else if (!(ft_strncmp(cmd, "pwd", 3)))
        *bui = PWD;
    else if (!(ft_strncmp(cmd, "export", 6)))
        *bui = EXPORT;
    else if (!(ft_strncmp(cmd, "unset", 5)))
        *bui = UNSET;
    else if (!(ft_strncmp(cmd, "env", 3)))
        *bui = ENV;
    else if (!(ft_strncmp(cmd, "cd", 2)))
        *bui = CD;
    else
        *bui = NONEXISTENT;
}

void    free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        tab[i] = NULL;
        free(tab[i]);
    }
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

void find_input(char **tab, t_info *info)
{
    int i;

    if (info->option == 0)
        i = 1;
    else if (info->option == 1)
        i = 2;

    while (t)
}

void    shell_loop()
{
    enum built_in_index bui;
    t_info info;
    int crashed;
    char *cmd;
    char **separated;
    char *cur_dir;

    init_built_in();
    crashed = FALSE;
    ft_printf(RED     "Welcome to Minisheh\n"     RESET);
    while (!crashed)
    {
        info.option = 0;
        cur_dir = get_cur_dir(&info);
        // directories();
        cmd = NULL;
        ft_printf(BLUE "~ ");
        ft_printf("%s%s" RESET, cur_dir, " > ");
        get_next_line(0, &cmd);
        separated = ft_split(cmd, ' ');
        if (separated[0] && separated[1] && !(ft_strncmp(separated[1], "-n", 2)))
        {
            info.option = 1;
            separated[0] = ft_strjoin(separated[0], separated[1]);
        }
        compare_cmd(separated[0], &bui);
        char *input = find_input(separated, &info);
        if (bui == 8)
            ft_printf("Invalid command bitch\n");
        else
            (*built_in[bui]) (cmd, &info);
        free_tab(separated);
    }    
}

int main()
{
    system("clear");
    shell_loop();
}