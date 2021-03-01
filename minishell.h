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

typedef struct	s_list
{
    struct s_list	*next;
    void			*data;
}				t_list;

typedef struct s_env
{
    char *value;
    char *key;
}               t_env;


typedef struct s_cmd
{
	char *cmd;
	char *input;
	char *output;
	int bui;
    char *option; // option tells program if an option is being used or not : 0 / 1
}               t_cmd;

typedef struct s_info
{
    char cur_path[PATH_MAX];
	t_list	*cmd_head;
    t_list  env;
    t_env   base_env;
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
int ft_env (t_cmd *cmd, char **envp);
int ft_cd (t_cmd *cmd);
void    compare_cmd(t_cmd *cmd);


// free

void    free_tab(char **tab);
void    free_everything(t_info *info, char **tab, char *cmd);

// linked lists

t_cmd   *create_cmd_struct();
t_list	*ft_create_elem(void *data);
void	ft_list_push_front(t_list **list, void *data);
int		ft_list_size(t_list *list);
t_list	*ft_list_last(t_list *list);
void	ft_list_push_back(t_list **begin_list, void *data);
// t_cmd	*ft_list_push_strs(int size, char **strs);
void	free_cmd_struct(void *data);
void	ft_list_clear(t_list *begin_list, void (*free_fct)(void *));
t_list	*ft_list_at(t_list *begin_list, unsigned int nbr);
/*void	ft_list_reverse(t_list **begin_list);*/

#endif
