/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:50:18 by root              #+#    #+#             */
/*   Updated: 2025/04/21 18:03:13 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                  LIBRARIES                                 */
/* ************************************************************************** */

# include <stdio.h> //printf
# include <unistd.h> //ttyslot, ttyname, isatty, chdir, close, read, open, write
# include <sys/stat.h> //fstat, lstat,stat
# include <fcntl.h> // stat struct ??????
# include <sys/wait.h> // wait()
# include <sys/types.h> //closedir, opendir
# include <sys/ioctl.h> //ioctl
# include <dirent.h> // closedir, readdir,opendir
# include <string.h> // perror, strerror
# include <stdlib.h> //getenv, malloc
# include <termios.h> //tcsetattr
# include <readline/history.h> //shell history
# include <readline/readline.h> //readline
# include <signal.h> // signal()
# include <stdbool.h> //bools
# include <errno.h> //strerror, errno
# include <linux/limits.h> //kernel macros
# include <limits.h> //macros
# include "libft/libft.h"
/* ************************************************************************** */
/*                                    MACROS                                  */
/* ************************************************************************** */
//colors
# define RED "\033[0;31m"
# define GR	"\033[0;32m"  
# define YLL "\033[0;33m"
# define BLU "\033[0;34m"
# define BLA "\033[0;30m"
# define CYA "\033[0;36m"
# define GREY "\033[0;90m"
# define BBLA "\033[30;1m"
# define BRED "\033[31;1m"
# define BGR "\033[32;1m"
# define BYLL "\033[33;1m"
# define BBLU "\033[34;1m"
# define BMAG "\033[35;1m"
# define BCYA "\033[36;1m"
# define BWHI "\033[37;1m"
# define RES "\033[0m"

//error messages
/*
# define ERR_MEM "Error allocating memory\n"
# define ERR_STDIN "Error with stdin\n"
# define ERR_PRC "Error creating process\n"
# define ERR_ENVP "Error duplicating environment variables\n"
*/
# define ERR_CNOTFOUND "command not found\n"
# define ERR_SYN_EMPT "Command '' not found\n"
# define ERR_SYN_SQT "msh: syntax error - unclosed single quotes\n"
# define ERR_SYN_DQT "msh: syntax error - unclosed double quotes\n"
# define ERR_SYN_PIPE "msh: syntax error near unexpected token `|'\n"
# define ERR_SYN_REDIR_NL "msh: syntax error near unexpected token `newline'\n"
# define ERR_SYN_REDIR_HD "msh: syntax error near unexpected token `<<'\n"
# define ERR_SYN_REDIR_HD_OPEN "msh: syntax error heredoc open `<<'\n"
# define ERR_SYN_REDIR_IN "msh: syntax error near unexpected token `<'\n"
# define ERR_SYN_REDIR_OUT "msh: syntax error near unexpected token `>'\n"
# define ERR_SYN_REDIR_APP "msh: syntax error near unexpected token `>>'\n"
# define ERR_SYN_UNS_OP "msh: syntax error - unsupported operator\n"
# define ERR_CD_ARGS "msh: cd: too many arguments\n"
# define ERR_UNKRED "unknown redirection type\n"

//constants
# define WHITESPACE " \t\n\r\v\f"
# define OPERATOR "|<>"
# define NON_EOF "|<>&" //check if there are more
# define REDIR "<>"
# define QUOTE "\"\'"
/* ************************************************************************** */
/*                                   STRUCTS                                  */
/* ************************************************************************** */

typedef enum e_cmd_type
{
	//EXEC,
	ECH,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	//CLEAR,
	EXIT,
	//HELP,
	//PATH
}	t_cmd_type;

typedef enum e_tk_type
{
	PIPE, // |
	WORD, // cmd or arg
	BT_CMD, //builtin cmd
	ARG, //arg for cmd
	W_SPACE, //space
	FILE_NAME,
	REDIR_IN, // < (input)
	REDIR_OUT, // > (output)
	REDIR_APP, // >> (append)
	REDIR_HD, // << (heredoc)
	ENV_CMD, // envirm. cmd
}	t_tk_type;

typedef struct s_tk_lst
{
	t_tk_type		type;
	char			*content;
	struct s_tk_lst	*next;
	struct s_tk_lst	*prev;
}	t_tk_lst;

typedef struct s_tree_nd
{
	t_tk_type			type;
	char				*op_content;
	char				**cmd_content;
	bool				eof_ch;
	char				**args;
	char				*cmd;
	t_tk_type			cmd_type;
	char				*file;
	char				*tmp_file;
	int					fd;
	struct s_tree_nd	*left;
	struct s_tree_nd	*right;
}	t_tree_nd;

typedef struct t_msh
{
	bool		active;
	char		*dir;
	int			msh_pid;
	char		*prompt_line;
	t_tk_lst	*token_list;
	t_tree_nd	*tree_root;
	char		**envp;
	t_list		*envp_list; //enviroment variables line user, home, path, etc
	bool		debug_mode;
	bool		hd_check;
}	t_msh;

typedef struct s_redir_data
{
	int			orig_stdin;
	int			orig_stdout;
	t_tree_nd	*cmd_nd;
}	t_redir_data;

typedef struct s_quote_state
{
	bool	in_quotes;
	char	quote_char;
}	t_quote_state;

/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */

/************ 00_main ************/
//00_main.c
int				main(int ac, char **av, char **envp);
void			prompt_and_read(t_msh **msh);

/************ 10_init ************/
//10_init_msh.c
void			ft_init_msh(t_msh **msh, char **envp);
void			prompt_and_read(t_msh **msh);
char			*get_prompt(void);

//11_envp_copies.c
void			copy_envp(t_msh *msh, char **envp);
char			**envp_to_array(t_msh *msh, char **envp);
void			envp_to_list(t_msh *msh, char **envp);
char			*add_envp_newline(char *envp);

//12_init_utils.c
void			init_all_null(t_msh **msh);

/************ 20_syntax ************/
//20_syntax_check.c
bool			syntax_is_ok(t_msh **msh);
bool			any_of_these_syn(const char *line);
bool			unsupported_operators(const char *line);
void			exec_fake_hd(const char *line, int hd_index);

//21_syntax_quotes.c
bool			unclosed_quotes(const char *line);

//22_syntax_pipes.c
bool			misplaced_pipe(const char *line);
bool			pipe_at_beginning(const char *line);
bool			pipe_at_end(const char *line);
bool			consec_operators_pipe(const char *line);

//23_syntax_redir.c
bool			conseq_operators_redir(const char *line);
void			conseq_redir_r_case(const char *line, int i);
void			conseq_redir_l_case(const char *line, int i);
bool			misplaced_redir_at_end(const char *line);

//24_syntax_utils.c
bool			look_for_pipe(const char *line, int i);
bool			check_in_quotes(char c, bool *in_quotes);
int				check_if_hd(const char *line);
char			*get_eof(const char *line, int hd_index);

/************ 30_tokens ************/
//30_tokenizer.c
void			get_tokens(t_msh **msh, int i);
bool			extra_check(t_msh **msh, int *i, char c, t_quote_state quote);
void			sub_tokenize(t_msh **msh);
void			handle_filename(t_tk_lst *token_list);
char			*check_env_cmd(char *cmd, char *env_path, int i);

//31_token_words.c
int				token_is_word(t_msh **msh, int start);
int				token_is_word_in_quotes(t_msh **msh, int start,
					bool *in_quotes, char *quote_char);
int				token_is_space(t_msh **msh, int start);

//32_token_pipes_and_redir_r.c
int				token_is_pipe(t_msh **msh, int start);
int				redir_r(t_msh **msh, int start);
int				token_is_redir_app(t_msh **msh, const char *line,
					char *redir_app, int i);
int				token_is_redir_out(t_msh **msh, const char *line,
					char *redir_out, int i);

//33_token_redir_l.c
int				redir_l(t_msh **msh, int start);
int				token_is_redir_hd(t_msh **msh, const char *line,
					char *redir_hd, int i);
int				token_is_redir_in(t_msh **msh, const char *line,
					char *redir_in, int i);

//34_token_utils.c
void			check_quote(bool *in_quotes, char *quote_char, char c);
void			app_tk(t_msh *msh, t_tk_lst *new_tk,
					char *content, t_tk_type type);
char			*get_path(t_list *envp_list);
void			check_rep_cmd(t_msh **msh);

/************ 40_build_tree ************/
//40_tokens_to_tree.c
void			parse_line(t_msh **msh);
t_tree_nd		*new_tree_nd(t_tk_type *type, char *content);

//41_build_pipe_nodes.c
t_tree_nd		*build_pipe_nd(t_tk_lst **tokens);

//42_build_redir_nodes.c
t_tree_nd		*build_redir_nd(t_tk_lst **token_list);
t_tree_nd		*handle_redir(t_tree_nd *redir_nd, t_tk_lst **curr_tk,
					bool *cmd_exc);
t_tree_nd		*attach_redir(t_tree_nd *redir_nd, t_tree_nd *new_redir);
bool			check_cmd(t_tk_lst **token_list, bool cmd_exc);
t_tree_nd		*add_left(t_tree_nd *redir_nd, t_tree_nd *cmd_nd, bool cmd_exc);

//43_build_cmd_nodes.c
t_tree_nd		*build_cmd_nd(t_tk_lst **token_list);
void			handle_cmd(t_tree_nd *cmd_nd, t_tk_lst **curr_tk,
					t_list **args);
char			**join_cmd_and_args(char *cmd, char **args);
t_list			*reverse_args(t_list **head);

//44_tree_utils.c
t_tk_lst		*safe_next_tk(t_tk_lst *curr_tk);
bool			type_is_redir(t_tk_type *type);
bool			type_is_word(t_tk_type *type);
bool			type_is_cmd(t_tk_type *type);
bool			type_is_arg(t_tk_type *type);

/************ 50_built_ins ************/
//50_pwd.c
int				ft_pwd(void);

//51_cd.c
int				ft_cd(t_msh **msh, t_tree_nd **node);
int				get_dir(t_tree_nd **node, char **target_dir);
int				update_cd_env(t_msh **msh, char *old_pwd);

//52_env.c
int				print_env(t_msh **msh, t_tree_nd **node);
int				update_env_var(t_list **env_list, const char *var_name,
					const char *content);
void			add_new_env_var(t_list **env_list, const char *var_name,
					const char *data);

//53_echo.c
int				ft_echo(t_tree_nd **node);

//54_exit.c
void			ft_exit(t_msh **msh, t_tree_nd **node);	
unsigned int	ft_convert_value(t_msh **msh, char *code);
int				ft_exit_value(t_msh **msh, int exit_code, int update_exit,
					int exit_msh);
int				ft_strnumeric(char *str, t_msh **msh);

//55_unset.c
int				ft_unset(t_msh **msh, t_tree_nd **node);
void			ft_delete_var(t_list **env_list, const char *var_name);

//56_export.c

/************ 60_exec_tree ************/
//60_exec_tree.c
void			exec_tree(t_msh **msh, t_tree_nd *node);

//61_expand_tree.c
void			expand_tree(t_msh **msh, t_tree_nd *node);
void			expand_tk(t_msh **msh, char **args);
char 			*get_env_content(t_list *envp_list, char *key_word);

//612_exec_pipe.c
void			exec_pipe(t_msh **msh, t_tree_nd *node);
void			perform_left_pipe(int useless_fd, int dup_fd, int curr_pid);
void			perform_right_pipe(int useless_fd, int dup_fd, int curr_pid);

//63_exec_redir.c
void			exec_redir_before_cmd(t_msh **msh, t_tree_nd *node);
int				exec_redir(t_tree_nd *node);
int				create_file_fd(t_tk_type type, char *file_name);
int				collect_redirs_and_cmd(t_tree_nd **curr_nd,
					t_tree_nd **redir_nd, t_redir_data *redir_data);

//64_exec_heredoc.c
void			exec_heredocs(t_tree_nd *node);
void			handle_hd(t_tree_nd *node, int hd_fd);
char			*check_eof(t_tree_nd *node, char *file_name);

//65_exec_cmd.c
void			exec_cmd(t_msh **msh, t_tree_nd *node);
void			exec_bt_cmd(t_msh **msh, t_tree_nd *node);
void			exec_env_cmd(t_msh **msh, t_tree_nd *node);

//66_exec_utils.c
int				safe_fork(void);
int				safe_dup(int old_fd, int curr_pid);
void			safe_dup2(int new_fd, int old_fd, int curr_pid);
int				safe_pipe(int pipe_fd[2]);

/************ 7_close_and_free ************/
//70_free_msh.c
void			free_msh(t_msh *msh);
void			free_tokens(t_tk_lst *token_list);
void			free_prompt_line(t_msh **msh);
void			free_tree(t_tree_nd *node);

//71_close_msh.c
void			close_minishell(t_msh	*msh, int exit_code);
void			envp_fail(t_msh *msh, char *str, t_list *list_nd, char *array);

/************ others ************/
//11_debug_utils.c
void			print_tokens(t_msh **msh);
void			print_envp_in_struct(t_msh **msh);
void			print_tree(t_tree_nd *node);

#endif
