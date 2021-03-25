/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:55:52 by lpellier          #+#    #+#             */
/*   Updated: 2021/03/25 15:35:34 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <termios.h>
# define TRUE 1
# define FALSE 0
# define RED "\033[31m"
# define BLUE "\033[34m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

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
** pointer on next struct of linked list
** pointer on data, usually data is a struct
*/

typedef struct	s_list
{
	struct s_list	*next;
	void			*data;
}				t_list;

typedef struct	s_cursor
{
	int				posx;
	int				posy;

	int				start_posx;
	int				start_posy;

	int				col;
	int				lin;
}				t_cursor;

typedef struct	s_info
{
	struct	termios termios_p;
	int		(*built_in[9])(int index_cmd);
	char	cur_path[PATH_MAX];
	int		crashed;
	int		cmd_status;
	int		nb_pipe;
 	int		nb_l_redir;
 	int		nb_r_redir;
 	int		nb_rd_redir;
 	int		nb_colon;
	int		cur_in_history;
	int		prompt_len;
	t_cursor cursor;
	t_list	*cmd_head;
	t_list	*env_head;
	t_list	*history_head;
	char	*output;
	char	**envp;
	char	**dir_paths;
}				t_info;

t_info			info;

/*
** #define SEPARATOR "|'<;>\""
*/

enum			built_in_index
{
	ECHOO,
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

// int main(int ac, char **av, char **envp);

void		update_cmd_status();
int			shell_loop(char **envp);
int			get_pos(int *x, int *y);
char		*print_last_cmd();
char		*print_prev_cmd();
char	*delete_char(char *str, int index);
/*
** termcap
*/

char		*check_for_arrows(int *index);


/*
** utils
*/

int			pipe_or_colon(char c);
int			is_whitespace(char c);
int			spaces(char *s);
int			check_sep(char *line);

/*
** test
*/

void		print_cmd_info(t_cmd *cmd);

/*
** parsing
*/

char		*read_everything();
int			get_input(char *line, t_cmd *cmd);
int			get_cmd(char *line, t_cmd *cmd);
char		*str_replace(char *orig, char *rep, char *with);
char		*replace_dollars_env(char *line);
void			read_line(int first);
void			read_cmd(char *line, int index, int index_cmd);
char			*get_cur_dir();
int				directories(char *path, char *cmd);

/*
** init
*/

void reset_info();
void		init_info(char **envp);
void		init_termcap();
void			init_built_in();

/*
** built-in
*/

void		store_output(int index_cmd);
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

char		**count_args(t_cmd *cmd, int *count);
char		**list_to_tab(t_list *begin_list);
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
