/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:55:52 by lpellier          #+#    #+#             */
/*   Updated: 2021/05/06 14:33:22 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
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
# define TILDE 126
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
	char			**args;
	char			*path;
	char			*saved_env_arg;
	int				**lint;
	int				bui;
	int				arg_index; // keeps track of current position in cmd
	int				limit_index; // is set to wherever next pipe or end of cmd is
	int				arg_nbr;
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
	int				posy;
	int				posx;
}					t_history;

/*
** pointer on next struct of linked list
** pointer on data, usually data is a struct
*/

typedef struct s_signal
{
	int				kill;
	int				bin_running;
}					t_signal;

typedef struct s_cursor
{
	int				posx;
	int				posy;
}					t_cursor;

typedef struct s_terminfo
{
	int				echo_padding;
	int				prompt_len;
	int				col;
	int				lin;
}					t_terminfo;

typedef struct s_info
{
	struct termios	termios_p;
	struct termios	saved_term;
	t_cursor		cursor;
	t_terminfo		terminfo;
	t_list			*cmd_head;
	t_list			*env_head;
	t_list			*history_head;
	char			**envp;
	char			**cmd_tab;
	char			**dir_paths;
	char			*line;
	int				*lint;
	int				lint_index;
	int				line_index;
	int				index_cmd;
	int				cur_in_history;
	int				crashed;
	int				debug_option;
	int				exit_code;
	int				(*built_in[10])();
}					t_info;

t_signal			*g_signal;

enum				e_separator
{
	NOTHING,
	PIPE,
	R_LEFT,
	R_RIGHT,
	R_RIGHTD
};

enum				e_line_indicators
{
	_EMPTY,
	_CHAR,
	_SEP,
	_QUOTED, 
	_DQUOTED,
	_DOLLAR,
	_BSPACED,
	_DOLLARED,
	_EMPTY_CHAR
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

/*********
** main **
**********/

/*************
** built-in **
*************/

// binary_things
int			binary_process(t_info *info, t_cmd *cmd);
int			exec_binary(t_info *info, t_cmd *cmd);
int			check_in_path(t_info *info, t_cmd *cmd, int arg_index);
int			find_binary(t_info *info, t_cmd *cmd);

// built_in
char		last_char(char *str);
int			str_isalpha_withplus(char *str);

// echo_things
int			ft_echo_n(t_info *info, t_cmd *cmd);
int			ft_echo(t_info *info, t_cmd *cmd);
int			only_n(char *str);

// pure_shell
int			ft_pwd(t_info *info, t_cmd *cmd);
int			ft_exit(t_info *info, t_cmd *cmd);
int			arg_is_option(char *arg);
int     	str_is_alpha(char *str);
int			print_error(char *cmd, char *arg, char *error, int code);

// built_in2
char		*define_path(t_info *info, t_cmd *cmd, int arg_index);
char		**list_to_tab(t_list *begin_list);
char		*get_actual_cmd(char *cmd, char **path);
void    	update_pwd(t_info *info);

// cd_things
int			ft_cd(t_info *info, t_cmd *cmd);
int			just_secure_free(char *path);
int			check_for_cdpath(t_info *info, char **path);

// env_things
int			ft_unset(t_info *info, t_cmd *cmd);
int			ft_env(t_info *info, t_cmd *cmd);

// cmp_size_and_cmp
int			compare_size(char *s1, char *s2);
void		compare_cmd(t_info *info, t_cmd *cmd);

// do_export
int			export_error(char *str, char *key, char *value);
int			print_declare_env(t_info *info);
int			ft_export(t_info *info, t_cmd *cmd);
int			export_content(t_info *info, char *str);
void		modify_export(t_info *info, char *key, char *value);

// key_n_value_error
int			value_error(char *key, char *value);
int			key_error(char *key);

/*********
** free **
*********/

// free
void		free_tab(char ***tab);
void    	free_lint_tab(int arg_nbr, int ***tab);
void		free_history_struct(void *data);
void		free_cmd_struct(void *data);
void		free_env_struct(void *data);

/************
** parsing **
************/

// directories
char		*get_cur_dir(void);
int			directories(char *path, char *cmd);

// parsing_space
int			is_whitespace(char c);

// char_and_int
void		intcat(int *dest, int start, int *src);
void		remove_int(int	*lint, int index);
void		remove_char(char *line, int index);
void		add_int(int *dest, int key, int index);
void		add_char(char *dest, char key, int index);

// key_move
void		move_left(t_info *info);
void		move_right(t_info *info, char *dest);

// char_and_key
int			*sublint(int *src, int index);
void		add_key(t_info *info, char *dest, char key);
void		delete_key(t_info *info, char *dest);

// parsing
int			str_isalpha_withminus(char *str);
int			count_args(t_info *info, char *line, int *lint);
int			pipe_in_args(t_cmd *cmd, int start);
int			redir_in_args(t_cmd *cmd, int start);
int			sep_in_args(t_cmd *cmd, int start);
int			exec_cmd(t_info *info, t_cmd *cmd, int piped);
int			redir_in_cmd(t_cmd *cmd);
int			multiple_args_after_redir(t_cmd *cmd);
int			str_isalpha_withminus(char *str);
void		update_arg_index(t_cmd *cmd, int start);
void		bzero_lint(int *lint, int size);
void		init_cmd_lint(t_info *info, t_cmd *cmd);
void		split_by_empty(t_info *info, t_cmd *cmd, char *line, int arg_nbr);
void		read_cmd(t_info *info, char *line);

// error_handling
int			check_syntax(t_info *info);
int			pipe_error_syntax(t_info *info, int i);
int			double_error_syntax(t_info *info, int i, char token);

// colon_count_split
char		**split_by_colon(t_info *info, char *line, int *lint);
int			count_cmd(char *line, int *lint);
void		create_cmd_list(t_info *info, int nbr);

// read_everything
int			read_line(t_info *info);
int			read_keys(t_info *info, char key, t_history *cur);
void		process_line(t_info *info, int first);
void		set_n_first(t_info *info, int first);
void		init_info_n_term(t_info *info);

// redir_and_swap
int			is_redir(t_cmd *cmd, int i);
int			is_pipe(t_cmd *cmd, int i);
void		swap_args(t_cmd *cmd, int arg_index_one, int arg_index_two);
void		modify_line_redir(t_cmd *cmd, int i);
void		move_first_redir(t_cmd *cmd);

// read_everything_suite
int			pass_q_and_dq(char *line, int i);
void		update_history(t_info *info, t_history *cur);
void		bzero_and_cpy(t_history *cur, char *line);
void		special_keys(t_info *info, char key);
void		toggle(int *bo, int *index);

// backsl_and_quote
int			backslash(t_info *info, int *index, int dquote);
int			quote(t_info *info, int *index);
int			dquote(t_info *info, int *index);
int			is_empty_or_void(int lint);
void		add_empty_char(t_info *info, int count, int index);

// transform
int			transform_line(t_info *info, int index, int quote_nb, int dquote_nb);

// control_and_dollar
int			control_d(t_info *info);
int			ft_isalpha_ordollar(int c);
int			dollar(t_info *info, char *cmd_line, int start);
void		dollar_suite(t_info *info, char *cmd_line, char *var, int start, int quote);

// colon_and_count
int			count_exceptions(int quote, int dquote);

/**********
** redir **
**********/

// do_pipe
int			pipe_for_exec(t_info *info, t_cmd *cmd);
int			child_process(t_info *info, t_cmd *cmd, int *pipefd);
int			get_child(t_info *info, t_cmd *cmd, pid_t cpid, int pipefd[2]);
void		free_in_children(t_info *info);
void		interpret_errors(t_info *info);

// do_redir
int			restore_std(pid_t saved_stdin, pid_t saved_stdout, int file_fd);
int			create_next_file(t_cmd *cmd, int start);
int			redir(t_info *info, t_cmd *cmd);
int			create_files(t_cmd *cmd);
void		save_std(pid_t *saved_stdin, pid_t *saved_stdout);

// redir_std
int			arg_is_dollared(t_cmd *cmd, int index);
int			arg_is_empty(t_cmd *cmd, int index);
int			space_in_arg(t_cmd *cmd, int index);
int			open_file(t_cmd *cmd, int start, int separator);
int			ft_cinset(const char c, const char *set);

/***************
** shell_init **
***************/

// begin_shell
int			delete_empty_history(void *data, void *data_ref);
int			shell_loop(t_info *info);
int			check_exec_options(t_info *info, int argc, char **argv);
void		print_prompt(t_info *info);
void		update_cmd_status(t_info *info, int new_code);

// init_info
int			init_info(t_info *info, char **envp);
void		reset_info(t_info *info);

// init
int			init_terminal(t_info *info);
int			init_env(t_info *info, char **envp);
void		set_lint(t_info *info, int *lint);
void		reset_dir_paths(t_info *info);
void		init_built_in(t_info *info);

/*************
** skeleton **
*************/

// struc_env
int			modify_env(t_info *info, char *key, char *new_value, int concat);
t_env		*get_env_custom(t_info *info, char *key);

// structs
t_cmd		*create_cmd_struct(void);
t_env		*create_env_struct(char *key, char *value);
t_history	*create_history_struct(void);


// print_and_cmp
int			cmp_env(void *data, void *data_ref);
void		print_env_struct(void *data);
void		print_env_declare(void *data);

/************
** termcap **
************/

// termcap
void		init_termcap(t_info *info);

// termcap_utils
void		check_for_arrows(t_info *info, char *line);
void		restore_term(t_info *info);
void		clear_line(t_info *info);
void		print_last_cmd(t_info *info, char *line);
void		print_prev_cmd(t_info *info, char *line);

// all_signal
void		ft_sigint(int sig);
void		ft_sigquit(int sig);

/*********
** test **
*********/

// testing_func
void		print_cmd_info(t_cmd *cmd);

#endif
