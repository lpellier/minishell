/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:55:52 by lpellier          #+#    #+#             */
/*   Updated: 2021/04/27 10:46:54 by lpellier         ###   ########.fr       */
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
	int				bui;
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
	char			**dir_paths;
	char			*line;
	int				*lint;
	int				lint_index;
	int				line_index;
	int				index_cmd;
	int				cur_in_history;
	int				crashed;
	int				debug_option;
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
	_TOKEN,
	_QUOTED,
	_DQUOTED,
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

void		clear_line(t_info *info);
int			is_empty_or_void(int lint);
int			count_args(t_info *info, char *line, int *lint);
void		set_lint(t_info *info, int *lint);
int			init_terminal();
int			print_error_option(t_cmd *cmd);
int			print_error(char *error);
void		move_right(t_info *info, char *dest);
void		move_left(t_info *info);
void		print_prompt(t_info *info);
int			delete_empty_history(void *data, void *data_ref);
int			shell_loop(t_info *info);
void		update_cmd_status(t_info *info, int new_code);
int			check_exec_options(t_info *info, int argc, char **argv);

/*************
** built-in **
*************/

// binary_things
int			exec_binary(t_info *info);
int			find_binary(t_info *info, t_cmd *cmd);
void		exec_binary_check(t_cmd *cmd, char **argv, char **split);

// built_in
char		last_char(char *str);
int			str_isalpha_withplus(char *str);

// pure_shell
int			ft_pwd();
int			ft_exit();
int			ft_echo_n();
int			ft_echo();
int			only_n(char *str);

// built_in2
char		**list_to_tab(t_list *begin_list);
char		*get_actual_cmd(char *cmd, char **path);
int			ft_cd();
int			nothing();

// env_things
int			ft_unset();
int			print_declare_env(void);
int			ft_env();

// cmp_size_and_cmp
int			compare_size(char *s1, char *s2);
void		compare_cmd(t_info *info, t_cmd *cmd);

// do_export
int			ft_export();
int			export_error(t_cmd *cmd);
int			export_remove_char(char **key_value);
void		modify_export(char *key, char *value, int concat);

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

/************
** parsing **
************/

// directories
char		*get_cur_dir(void);
int			directories(char *path, char *cmd);

// parsing_space
int			is_whitespace(char c);

// char_and_key
void		add_char(char *dest, char key, int index);
void		remove_char(char *line, int index);
void		add_key(t_info *info, char *dest, char key);
void		delete_key(t_info *info, char *dest);

// parsing
int			str_isalpha_withminus(char *str);
void		read_cmd(t_info *info, char *line);

// error_handling
int			check_syntax(t_info *info);
int			pipe_error_syntax(t_info *info, int i);
int			double_error_syntax(t_info *info, int i, char token);

// colon_count_split
void		create_cmd_list(t_info *info, int nbr);
int			count_cmd(char *line, int *lint);
char		**split_by_colon(t_info *info, char *line, int *lint);

// read_everything
int			read_line(t_info *info);
int			read_keys(t_info *info, char key, t_history *cur);
void		process_line(t_info *info, int first);
void		modify_line_redir(char *str);

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
int			transform_line(t_info *info, int index, int quote_nb, int dquote_nb);

// control_and_dollar
int			control_d(t_info *info);
int			ft_isalpha_ordollar(int c);
int			dollar(t_info *info, int *index, int quote);
void		dollar_suite(t_info *info, char *var, int *index, int i, int quote);

// colon_and_count
int			count_exceptions(int quote, int dquote);

/**********
** redir **
**********/

// do_redir
void		save_std(pid_t *saved_stdin, pid_t *saved_stdout);
int			restore_std(pid_t saved_stdin, pid_t saved_stdout, int file_fd);
int			redir(t_info *info, char *line, int index, int separator);
void		redir_something(t_info *info, char *line, int index);

// do_pipe
int			pipe_for_exec(t_info *info, char *line, int separator);
int			child_process(t_info *info, int separator, t_cmd *cmd, \
				int *pipefd);
void		get_child(t_info *info, int separator, pid_t cpid);
void		check_pipe(t_info *info, int separator);

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

/****************
** redirection **
****************/

char		*ft_strncpy(char *dest, char *src, unsigned int n);
char		*ft_strtrim(char const *s1, char const *set);
int			open_file(t_info *info, int separator, char *line, int *index);
int			ft_isspace(int c);
int			ft_cinset(const char c, const char *set);
int			ft_isseparator(int c);
int			ft_checkc(char c, const char *set);

/***************
** shell_init **
***************/

// init
int			init_env(t_info *info, char **envp);
void		reset_info(t_info *info);
int			init_info(t_info *info, char **envp);
void		init_built_in(t_info *info);

/*************
** skeleton **
*************/

// struc_env
t_env		*get_env_custom(t_info *info, char *key);
int			modify_env(t_info *info, char *key, char *new_value, int concat);

// structs
t_cmd		*create_cmd_struct(void);
t_env		*create_env_struct(char *key, char *value);
t_history	*create_history_struct(void);


// print_and_cmp
int			cmp_env(void *data, void *data_ref);
void		print_env_struct(void *data);
void		print_history(void *data);
void		print_env_declare(void *data);

/************
** termcap **
************/

// termcap
void		init_termcap(t_info *info);

// termcap_utils
void		check_for_arrows(t_info *info, char *line);
void		restore_term(t_info *info);
void		print_last_cmd(t_info *info, char *line);
void		print_prev_cmd(t_info *info, char *line);

// all_signal
void		ft_sigint(int sig);
void		ft_sigquit(int sig);

/*********
** test **
*********/

void		print_cmd_info(t_cmd *cmd);

#endif
