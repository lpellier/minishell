/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:55:52 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/08 17:15:10 by tefroiss         ###   ########.fr       */
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
# define BSLASH 92
# define QUOTE 39
# define DQUOTE 34
# define DOLLAR 36
# define COLON 59
# define LINE_MAX 4096
# define RED "\033[31m"
# define BLUE "\033[34m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"
# define SEPARATOR "|<;>"

/*
** the cmd part of the command -- i.e. 'echo' or 'pwd' etc
** the input part of the command -- i.e. "allo" or ".."
** number assigned to one of the built in function
** bui stands for built-in-index
** the option part of the command -- i.e. "-n"
** path of binary if it is is one
*/

typedef struct s_cmd
{
	char			*cmd;
	char			*input;
	int				bui;
	char			*option;
	char			*path;
}					t_cmd;

/*
** the key part of the env var -- i.e. "user"
** the value part of the env var -- i.e. "lucaspellier"
*/

typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

typedef struct s_history
{
	char			*line;
}					t_history;

typedef struct	s_block
{
    int		start;
	int		end;
}				t_block;

/*
** pointer on next struct of linked list
** pointer on data, usually data is a struct
*/

typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}					t_list;

typedef struct s_cursor
{
	int				posx;
	int				posy;
	int				start_posx;
	int				start_posy;
	int				col;
	int				lin;
}					t_cursor;

typedef struct s_info
{
	struct termios	termios_p;
	int				(*built_in[9])(int index_cmd);
	char			cur_path[PATH_MAX];
	int				crashed;
	int				cmd_status;
	int				cur_in_history;
	int				prompt_len;
	int				echo_padding;
	t_cursor		cursor;
	t_list			*cmd_head;
	t_list			*env_head;
	t_list			*block_head;
	t_list			*history_head;
	char			*output;
	char			**envp;
	char			**dir_paths;
}					t_info;

t_info				g_info;

enum				e_separator
{
	NOTHING,
	PIPE,
	R_LEFT,
	R_RIGHT,
	R_RIGHTD
};

enum				e_built_in_index
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

enum				e_status_codes
{
	SUCCESS,
	FAILURE,
	OTHER
};

void		remove_char(char *line, int index);
// int main(int ac, char **av, char **envp);

void		update_cmd_status(void);
int			shell_loop(char **envp);
int			get_pos(int *x, int *y);
void		print_last_cmd(char *line);
void		print_prev_cmd(char *line);
int			modify_env(char *key, char *new_value, int concat);
void		delete_char(char *line, char *str, int index);

/*
** skeleton
*/

int			modify_env(char *key, char *new_value, int concat);
t_env		*get_env_custom(char *key);
t_cmd		*create_cmd_struct(void);
t_env		*create_env_struct(char *key, char *value);
t_block		*create_block_struct(int a, int b);
t_history	*create_history_struct(void);

/*
** termcap
*/

void		check_for_arrows(char *line);

/*
** utils
*/

int			check_sep(char *line, t_cmd *cmd);

/*
** test
*/

void		print_cmd_info(t_cmd *cmd);

/*
** parsing
*/

char		*read_everything(void);
char		*str_replace(char *orig, char *rep, char *with);
char		*replace_dollars_env(char *line);
char		*get_cur_dir(void);
int			backslash(char *line, int *index, int dquote);
int			count_exceptions(int quote, int dquote);
int			quote(char *line, int *index);
int			dquote(char *line, int *index);
int			transform_line(char *line, int index, int quote_nb, int dquote_nb);
int			is_there_colon_in_line(char *line);
int			control_d(char *line);
int			ft_isalpha_ordollar(int c);
int			dollar(char *line, int *index);
int			is_whitespace(char c);
int			spaces(char *s);
int			is_redir_l(char c);
int			is_redir_r(char c);
int			is_pipe(char c);
int			is_colon(char c);
int			get_input(char *line, t_cmd *cmd, int index);
int			get_cmd(char *line, t_cmd *cmd, int index);
int			get_option(char *line, t_cmd *cmd, int index);
int			directories(char *path, char *cmd);
int			is_whitespace(char c);
int			spaces(char *s);
int			is_redir_l(char c);
int			is_redir_r(char c);
int			is_pipe(char c);
int			is_colon(char c);
int			get_input(char *line, t_cmd *cmd, int index);
int			get_cmd(char *line, t_cmd *cmd, int index);
int			get_option(char *line, t_cmd *cmd, int index);
int			directories(char *path, char *cmd);
int			check_if_block(int index);
void		read_line(int first);
void		read_cmd(char *line, int index, int index_cmd);
void		read_line(int first);
void		add_char(char *dest, char key, int index);
void		remove_char(char *line, int index);
void		add_key(char *dest, char key);
void		delete_key(char *dest);

/*
** init
*/

void		reset_info(void);
void		init_info(char **envp);
void		init_termcap(void);
void		init_built_in(void);

/*
** built-in
*/

void		store_output(int index_cmd);
int			ft_echo(int index_cmd);
int			ft_exit(int index_cmd);
int			ft_echo_n(int index_cmd);
int			ft_pwd(int index_cmd);
int			ft_export(int index_cmd);
int			ft_unset(int index_cmd);
int			ft_env(int index_cmd);
int			ft_cd(int index_cmd);
int			exec_binary(int index_cmd);
int			find_binary(t_cmd *cmd);
void		compare_cmd(t_cmd *cmd);
int			compare_size(char *s1, char *s2);
int			only_n(char *str);
int			str_isalpha_withplus(char *str);
char		last_char(char *str);


/*
** signal
*/

void		ft_sigint(int sig);
void		ft_sigquit(int sig);
void		ft_sigterm(int sig);

/*
** free
*/

void		secure_free(void *ptr);
void		free_tab(char ***tab);
void		free_history_struct(void *data);
void		free_cmd_struct(void *data);
void		free_env_struct(void *data);

/*
** redirection
*/

char		*ft_strncpy(char *dest, char *src, unsigned int n);
int			ft_isseparator(int c);
int			ft_isspace(int c);
int			ft_cinset(const char c, const char *set);
char		*get_file(char *s);
int			open_file(int separator, char *line, int *index);
void		ft_symbol(t_cmd *cmd);

/*
** linked lists
*/

char		**count_args(t_cmd *cmd, int *count);
char		**list_to_tab(t_list *begin_list);
int			pipe_for_exec(int index_cmd,
				char *line, int index, int piped);
int			redir(int index_cmd, char *line, int index, int separator);
int			init_env(char **envp);
int			cmp_env(void *data, void *data_ref);
void		print_history(void *data);
void		print_env_struct(void *data);

t_list		*ft_create_elem(void *data);
t_list		*ft_list_at(t_list *begin_list, unsigned int nbr);
t_list		*ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)());
int			ft_list_size(t_list *list);
void		ft_list_push_front(t_list **begin_list, void *data);
void		ft_list_push_back(t_list **begin_list, void *data);
void		ft_list_clear(t_list *begin_list, void (*free_fct)(void *));
void		ft_list_remove_if(t_list **begin_list, void *data_ref,
				int (*cmp)(), void (*free_fct)(void *));
void		ft_list_foreach(t_list *begin_list, void (*f)(void *));

#endif
