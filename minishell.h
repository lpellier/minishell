/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:55:52 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/23 11:05:08 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <termcap.h>
# define PATH_MAX 4096
# define TRUE 1
# define FALSE 0
# define RED "\033[31m"
# define BLUE "\033[34m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

/*
** #define SEPARATOR "|'<;>\""
*/

enum			built_in_index
{
	ECHO,
	ECHO_N,
	EXIT,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	CD,
	BINARY,
	NONEXISTENT
};

enum			status_codes
{
	SUCCESS,
	FAILURE,
	OTHER
};

/*
** pointer on next struct of linked list
** pointer on data, usually data is a struct
*/

typedef struct	s_list
{
	struct s_list	*next;
	void			*data;
}				t_list;

/*
** the key part of the env var -- i.e. "user"
** the value part of the env var -- i.e. "lucaspellier"
*/

typedef struct	s_env
{
	char	*key;
	char	*value;
}				t_env;

typedef struct	s_history
{
    char	*line;
}				t_history;

/*
** the cmd part of the command -- i.e. 'echo' or 'pwd' etc
** the input part of the command -- i.e. "allo" or ".."
** number assigned to one of the built in function
** bui stands for built-in-index
** the option part of the command -- i.e. "-n"
** path of binary if it is is one
*/

typedef struct	s_cmd
{
	char	*cmd;
	char	*input;
	int		bui;
	char	*option;
	char	*path;
}				t_cmd;

typedef struct	s_info
{
	int		(*built_in[9])(int index_cmd);
	char	cur_path[PATH_MAX];
	int		crashed;
	int		cmd_status;
	int		nb_pipe;
 	int		nb_l_redir;
 	int		nb_r_redir;
 	int		nb_rd_redir;
 	int		nb_colon;
	t_list	*cmd_head;
	t_list	*env_head;
	t_list	*history_head;
	char	*output;
	char	**envp;
	char	**dir_paths;
}				t_info;

t_info			info;

int				shell_loop();

/*
** parsing
*/

void			read_line(int first);
void			read_cmd(char *line, int index, int index_cmd);
char			*get_cur_dir();
int				directories(char *path, char *cmd);

/*
** init
*/

void			init_built_in();

/*
** built-in
*/

int				ft_echo(int index_cmd);
int				ft_exit(int index_cmd);
int				ft_echo_n(int index_cmd);
int				ft_pwd(int index_cmd);
int				ft_export(int index_cmd);
int				ft_unset(int index_cmd);
int				ft_env(int index_cmd);
int				ft_cd(int index_cmd);
int				exec_binary(int index_cmd);
int				find_binary(t_cmd *cmd);
void			compare_cmd(t_cmd *cmd);
int				compare_size(char *s1, char *s2);

/*
** signal
*/

void	ft_sigint(int sig);
void	ft_sigquit(int sig);
void	ft_sigterm(int sig);

/*
** free
*/

void			free_tab(char **tab);

void		free_history_struct(void *data);
void			free_cmd_struct(void *data);
void			free_env_struct(void *data);

void			print_env_struct(void *data);
int				cmp_env(void *data, void *data_ref);

/*
** linked lists
*/

int				pipe_for_exec(int index_cmd,
					char *line, int index, int piped);
int				init_env(char **envp);
void		print_history(void *data);
t_cmd			*create_cmd_struct();
t_history *create_history_struct(char *str);
t_env			*create_env_struct(char *key, char *value);
t_list			*ft_create_elem(void *data);
int				ft_list_size(t_list *list);
void			ft_list_push_front(t_list **begin_list, void *data);
void			ft_list_push_back(t_list **begin_list, void *data);
void			ft_list_clear(t_list *begin_list, void (*free_fct)(void *));
t_list			*ft_list_at(t_list *begin_list, unsigned int nbr);
void			ft_list_remove_if(t_list **begin_list, void *data_ref,
					int (*cmp)(), void (*free_fct)(void *));
void			ft_list_foreach(t_list *begin_list, void (*f)(void *));
t_list			*ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)());

#endif
