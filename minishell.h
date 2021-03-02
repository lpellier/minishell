#include <__wctype.h>

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#define PATH_MAX 4096
#define TRUE 1
#define FALSE 0
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

//#define GREEN   "\x1b[32m"
//#define YELLOW  "\x1b[33m"
//#define MAGENTA "\x1b[35m"

//#define SEPARATOR "|'<;>\""

enum built_in_index {
    ECHO,
    ECHO_N,
    EXIT,
    PWD,
    EXPORT,
    UNSET,
    ENV,
    CD,
	IN_PATH __unused, // in_path will be for binaries found in dirs in $PATH
    NONEXISTENT
};

// maybe will use this for return codes of all functions in code,
// for more consistency
/*enum status_codes {
    SUCCESS,
    FAILURE,
    OTHER
};*/

typedef struct	s_list
{
    // pointer on next struct of linked list
    struct s_list	*next;
    // pointer on data, usually data is a struct
    void			*data;
}				t_list;

typedef struct s_env
{
    // the value part of the env var -- i.e. "user"
    char *value;
    // the key part of the env var -- i.e. "lucaspellier"
    char *key;
}               t_env;


typedef struct s_cmd
{
    // the cmd part of the command -- i.e. 'echo' or 'pwd' etc
	char *cmd;
	// the input part of the command -- i.e. "allo" or ".."
	char *input;
    // this will eventually be useful for stocking what a command
    // should output so that we feed it to another cmd
	char *output;
	// number assigned to one of the built in function
	// bui stands for built-in-index
	int bui;
	// the option part of the command -- i.e. "-n"
    char *option;
}               t_cmd;

typedef struct s_info
{
    char cur_path[PATH_MAX];
    int crashed;
    // head of cmd linked list
	t_list	*cmd_head;
    // head of env linked list
	t_list  *env_head;
}               t_info;

int (*built_in[8]) (t_info *info, int index_cmd);

// _Noreturn permits shutting up warning about infinite loop
// don't leave it here, remove before validation
void    shell_loop();

// parsing

void read_line(t_info *info);
char *get_cur_dir(t_info *info);
//int    directories();

// init

void init_built_in();

// built-in

int ft_echo (t_info *info, int index_cmd);
int ft_exit (t_info *info, int index_cmd);
int ft_echo_n (t_info *info, int index_cmd);
int ft_pwd (t_info *info, int index_cmd);
int ft_export (t_info *info, int index_cmd);
int ft_unset (t_info *info, int index_cmd);
int ft_env (t_info *info, int index_cmd);
int ft_cd (t_info *info, int index_cmd);
void    compare_cmd(t_cmd *cmd);


// free

void    free_tab(char **tab);


void	free_cmd_struct(void *data);
void	free_env_struct(void *data);

void    print_env_struct(void *data);
int     cmp_env(void *data, void *data_ref);
// linked lists

t_cmd   *create_cmd_struct();
t_env   *create_env_struct(char *key, char *value);
t_list	*ft_create_elem(void *data);
void	ft_list_push_back(t_list **begin_list, void *data);
void	ft_list_clear(t_list *begin_list, void (*free_fct)(void *));
t_list	*ft_list_at(t_list *begin_list, unsigned int nbr);
void	ft_list_remove_if(t_list **begin_list, void *data_ref,
                          int (*cmp)(), void (*free_fct)(void *));
void	ft_list_foreach(t_list *begin_list, void (*f)(void *));


#endif
