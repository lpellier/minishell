#ifndef MINISHELL_H
#define MINISHELL_H

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
    char *input;
    int option; // option tells program if an option is being used or not : 0 / 1
}               t_info;

int (*built_in[8]) (char *cmd, t_info *info);

void    shell_loop();

// parsing

char *get_cur_dir(t_info *info);
int    directories();

// init

void    reset_info(t_info *info);
void init_built_in();

// built-in

int ft_echo (char *cmd, t_info *info);
int ft_exit (char *cmd, t_info *info);
int ft_echo_n (char *cmd, t_info *info);
int ft_pwd (char *cmd, t_info *info);
int ft_export (char *cmd, t_info *info);
int ft_unset (char *cmd, t_info *info);
int ft_env (char *cmd, t_info *info);
int ft_cd (char *cmd, t_info *info);
void    compare_cmd(char *cmd, enum built_in_index *bui);


// free

void    free_tab(char **tab);
void    free_everything(t_info *info, char **tab, char *cmd);

#endif