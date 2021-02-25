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
	IN_PATH,
    NONEXISTENT
};

typedef struct s_cmd
{
	char *cmd;
	char *input;
	int bui;
    char *option; // option tells program if an option is being used or not : 0 / 1
	struct s_cmd *next;
}               t_cmd;

typedef struct s_info
{
    char cur_path[PATH_MAX];
	t_cmd	*head;
}               t_info;

int (*built_in[8]) (t_cmd *cmd);

void    shell_loop();

// parsing

void read_line(t_info *info);
char *get_cur_dir(t_info *info);
int    directories();

// init

int    reset_info(t_info *info);
void init_built_in();

// built-in

int ft_echo (t_cmd *cmd);
int ft_exit (t_cmd *cmd);
int ft_echo_n (t_cmd *cmd);
int ft_pwd (t_cmd *cmd);
int ft_export (t_cmd *cmd);
int ft_unset (t_cmd *cmd);
int ft_env (t_cmd *cmd);
int ft_cd (t_cmd *cmd);
void    compare_cmd(t_cmd *cmd);


// free

void    free_tab(char **tab);
void    free_everything(t_info *info, char **tab, char *cmd);

// linked lists

t_cmd	*ft_create_elem(char *cmd, char *input, int bui, char *option);
void	ft_list_push_front(t_cmd **list, char *cmd, char *input, int bui, char *option);
int		ft_list_size(t_cmd *list);
t_cmd	*ft_list_last(t_cmd *list);
void	ft_list_push_back(t_cmd **begin_list, char *cmd, char *input, int bui, char *option);
// t_cmd	*ft_list_push_strs(int size, char **strs);
void	free_cmd(t_cmd *list);
void	ft_list_clear(t_cmd *begin_list);
t_cmd	*ft_list_at(t_cmd *begin_list, unsigned int nbr);
void	ft_list_reverse(t_cmd **begin_list);

#endif