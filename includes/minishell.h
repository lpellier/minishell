/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:55:52 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/20 19:19:06 by lpellier         ###   ########.fr       */
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
# define WHITESPACE "\t\n\r\v\f"

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

typedef struct s_block
{
	int				start;
	int				end;
}					t_block;

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
	struct termios	saved_term;
	int				(*built_in[10])(int index_cmd);
	char			cur_path[PATH_MAX];
	int				crashed;
	int				cmd_status;
	int				cur_in_history;
	int				prompt_len;
	int				echo_padding;
	int				kill;
	int				sig_status;
	int				colon_nbr;
	int				bin_running;
	int				debug_option;
	t_cursor		cursor;
	t_list			*cmd_head;
	t_list			*env_head;
	t_list			*block_head;
	t_list			*history_head;
	char			**envp;
	char			**dir_paths;
	char			*line;
	int				status;
}					t_info;

t_info				*g_info;

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

void		print_block(void *data);
void		restore_term();
int			print_declare_env();
void		print_env_declare(void *data);

int			rem_hist(void *data, void *data_ref);
int			shell_loop(void);
int			get_pos(int *x, int *y);
void		restore_term(void);
void		update_cmd_status(void);
void		print_last_cmd(char *line);
void		print_prev_cmd(char *line);
void		delete_char(char *line, char *str, int index);

/************
** termcap **
************/

void		check_for_arrows(char *line);

/*********
** test **
*********/

void		print_cmd_info(t_cmd *cmd);

/************
** parsing **
************/

// directories
char		*get_cur_dir(void);
int			directories(char *path, char *cmd);

// parsing_utils
int			is_pipe(char c);
int			is_colon(char c);
int			is_redir_l(char c);
int			is_redir_r(char c);

// parsing_space
int			is_whitespace(char c);
int			spaces(char *s, int index);

// char_and_key
void		add_char(char *dest, char key, int index);
void		remove_char(char *line, int index);
void		add_key(char *dest, char key);
void		delete_key(char *dest);

// get_something
int			get_input(char *line, t_cmd *cmd, int index);
int			get_cmd(char *line, t_cmd *cmd, int index);
int			get_option(char *line, t_cmd *cmd, int index);

// parsing
int			str_isalpha_withminus(char *str);
int			cmp_block(void *data, void *data_ref);
int			check_if_block(int index);
int			ft_set_index(char *line, t_cmd *cmd, int index);
void		read_cmd(char *line, int index, int index_cmd);

// read_everything
int			read_line(void);
int			read_keys(char key, t_history *cur);
void		bzero_and_cpy(t_history *cur, char *line);
void		special_keys(char key);
void		process_line(int first);

// backsl_and_quote
int			backslash(char *line, int *index, int dquote);
int			quote(char *line, int *index);
int			dquote(char *line, int *index);
int			transform_line(char *line, int index, int quote_nb, int dquote_nb);

// control_and_dollar
int			control_d();
int			ft_isalpha_ordollar(int c);
int			dollar(char *line, int *index);
void		dollar_suite(char *line, char *var, int *index, int i);

// colon_and_count
int			is_there_colon_in_line(char *line);
int			count_exceptions(int quote, int dquote);
void		remove_colons(char *line, int i);
void		do_colon_split(char	**colon_split, int i);

/*********
** init **
*********/

int			init_env(char **envp);
void		reset_info(void);
int			init_info(char **envp);
void		init_termcap(void);
void		init_built_in(void);

/*************
** built-in **
*************/

// binary_things
int			exec_binary(int index_cmd);
int			find_binary(t_cmd *cmd);
void		exec_binary_check(t_cmd *cmd, char **argv, char **split);

// built_in
char		last_char(char *str);
int			str_isalpha_withplus(char *str);

// pure_shell
int			ft_pwd(int index_cmd);
int			ft_exit(int index_cmd);
int			ft_echo_n(int index_cmd);
int			ft_echo(int index_cmd);
int			only_n(char *str);

// built_in2
char		**count_args(t_cmd *cmd, int *count);
char		**list_to_tab(t_list *begin_list);
char		*get_folder_path(char *cmd, char **actu_cmd);
int			ft_cd(int index_cmd);
int			nothing(int index_cmd);

// env_things
int			ft_unset(int index_cmd);
int			print_declare_env(void);
int			ft_env(int index_cmd);

// cmp_size_and_cmp
int			compare_size(char *s1, char *s2);
void		compare_cmd(t_cmd *cmd);

// do_export
int			ft_export(int index_cmd);
int			export_error(t_cmd *cmd);
int			export_remove_char(char **key_value);
void		modify_export(char **key_value, int concat);

// do_redir
void		save_std(pid_t *saved_stdin, pid_t *saved_stdout);
int			restore_std(pid_t saved_stdin, pid_t saved_stdout, int file_fd);
int			redir(int index_cmd, char *line, int index, int separator);
void		redir_something(char *line, int index, int index_cmd);

// do_pipe
int			pipe_for_exec(int index_cmd, char *line, int index, int piped);
int			child_process(int separator, int index_cmd, t_cmd *cmd, \
				int *pipefd);
void		get_child(int separator, int index_cmd, pid_t cpid);
void		check_pipe(int separator, char *line, int index, \
				int index_cmd);

/***********
** signal **
***********/

void		ft_sigint(int sig);
void		ft_sigquit(int sig);
void		ft_sigterm(int sig);

/*********
** free **
*********/

// secure_free
void		secure_free(void *ptr);

// free
void		free_tab(char ***tab);
void		free_history_struct(void *data);
void		free_cmd_struct(void *data);
void		free_env_struct(void *data);
void		ft_list_clear(t_list *begin_list, void (*free_fct)(void *));

/****************
** redirection **
****************/

char		*ft_strncpy(char *dest, char *src, unsigned int n);
int			ft_isseparator(int c);
int			ft_isspace(int c);
int			ft_cinset(const char c, const char *set);
char		*get_file(char *s);
int			open_file(int separator, char *line, int *index);
void		ft_symbol(t_cmd *cmd);

/*************
** skeleton **
*************/

// struc_env
t_env		*get_env_custom(char *key);
int			modify_env(char *key, char *new_value, int concat);

// structs
t_cmd		*create_cmd_struct(void);
t_env		*create_env_struct(char *key, char *value);
t_history	*create_history_struct(void);
t_block		*create_block_struct(int a, int b);

// create_and_push
t_list		*ft_create_elem(void *data);
void		ft_list_push_front(t_list **begin_list, void *data);
void		ft_list_push_back(t_list **begin_list, void *data);

// linked_lists
int			ft_list_size(t_list *list);
void		ft_list_foreach(t_list *begin_list, void (*f)(void *));
void		ft_list_remove_if(t_list **begin_list, void *data_ref,
				int (*cmp)(), void (*free_fct)(void *));
t_list		*ft_list_at(t_list *begin_list, unsigned int nbr);
t_list		*ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)());

// print_and_cmp
int			cmp_env(void *data, void *data_ref);
void		print_env_struct(void *data);
void		print_history(void *data);
void		print_env_declare(void *data);

#endif
