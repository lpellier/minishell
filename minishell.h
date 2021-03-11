/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:55:52 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/11 13:23:36 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
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

/*
** head of cmd linked list
** head of env linked list
*/

typedef struct	s_info
{
	char	cur_path[PATH_MAX];
	int		crashed;
	int		nb_pipe;
 	int		nb_l_redir;
 	int		nb_r_redir;
 	int		nb_rd_redir;
 	int		nb_colon;
	t_list	*cmd_head;
	t_list	*env_head;
	char	*output;
	char	**envp;
	char	**dir_paths;
}				t_info;

int				(*built_in[9])(t_info *info, int index_cmd);

int				shell_loop(char **envp);

/*
** parsing
*/

void			read_line(t_info *info);
void			read_cmd(char *line, t_info *info, int index, int index_cmd);
char			*get_cur_dir(t_info *info);
int				directories(char *path, char *cmd);

/*
** init
*/

void			init_built_in();

/*
** built-in
*/

int				ft_echo(t_info *info, int index_cmd);
int				ft_exit(t_info *info, int index_cmd);
int				ft_echo_n(t_info *info, int index_cmd);
int				ft_pwd(t_info *info, int index_cmd);
int				ft_export(t_info *info, int index_cmd);
int				ft_unset(t_info *info, int index_cmd);
int				ft_env(t_info *info, int index_cmd);
int				ft_cd(t_info *info, int index_cmd);
int				exec_binary(t_info *info, int index_cmd);
int				find_binary(t_info *info, t_cmd *cmd);
void			compare_cmd(t_info *info, t_cmd *cmd);
int				compare_size(char *s1, char *s2);

/*
** signal
*/

/*
** void	ft_sigquit(int sig);
** void	ft_sigint(int sig);
** void	ft_sigterm(int sig, t_info *info);
*/

/*
** free
*/

void			free_tab(char **tab);

void			free_cmd_struct(void *data);
void			free_env_struct(void *data);

void			print_env_struct(void *data);
int				cmp_env(void *data, void *data_ref);

/*
** linked lists
*/

int				pipe_for_exec(t_info *info, int index_cmd,
					char *line, int index, int piped);
int				init_env(t_info *info, char **envp);

t_cmd			*create_cmd_struct();
t_env			*create_env_struct(char *key, char *value);
t_list			*ft_create_elem(void *data);
int				ft_list_size(t_list *list);
void			ft_list_push_back(t_list **begin_list, void *data);
void			ft_list_clear(t_list *begin_list, void (*free_fct)(void *));
t_list			*ft_list_at(t_list *begin_list, unsigned int nbr);
void			ft_list_remove_if(t_list **begin_list, void *data_ref,
					int (*cmp)(), void (*free_fct)(void *));
void			ft_list_foreach(t_list *begin_list, void (*f)(void *));
t_list			*ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)());

#endif
