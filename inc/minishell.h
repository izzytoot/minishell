/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:50:18 by root              #+#    #+#             */
/*   Updated: 2025/04/17 15:16:22 by icunha-t         ###   ########.fr       */
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
# include <linux/limits.h> //macros
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

typedef enum e_token_type
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
}	t_token_type;

typedef struct s_token_lst
{
	t_token_type		type;
	char				*content;
	struct s_token_lst	*next;
	struct s_token_lst	*prev;
}	t_token_lst;

typedef struct s_tree_node
{
	t_token_type		type;
	char				*op_content;
	char				**cmd_content;
	bool				eof_ch;
	char				**args;
	char				*cmd;
	t_token_type		cmd_type;
	char				*file;
	char				*tmp_file;
	int					fd;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
	struct s_tree_node	*straight;
}	t_tree_node;

typedef struct s_minishell
{
	bool		active;
	char		*dir;
	int			msh_pid;
	char		*prompt_line;
	t_token_lst	*token_list;
	t_tree_node	*tree_root;
	char		**envp;
	t_list		*envp_list; //enviroment variables line user, home, path, etc
	bool		debug_mode;
	bool		hd_check;
}	t_minishell;

typedef	struct s_redir_data
{
	int			orig_stdin;
	int			orig_stdout;
	t_tree_node	*cmd_node;
}	t_redir_data;

/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */

/************ 00_main ************/
//01_main.c
int			main(int ac, char **av, char **envp);
void		prompt_and_read(t_minishell **msh);

/************ 10_init ************/
//10_init_msh.c
void		ft_init_msh(t_minishell **msh, char **envp);
void		prompt_and_read(t_minishell **msh);
char		*get_prompt(void);

//11_envp_copies.c
void		copy_envp(t_minishell *msh, char **envp);
char		**envp_to_array(t_minishell *msh, char **envp);
void		envp_to_list(t_minishell *msh, char **envp);
char		*add_envp_newline(char *envp);

//12_init_utils.c
void		init_all_null(t_minishell **msh);

/************ 20_syntax ************/
//20_syntax_check.c
bool		syntax_is_ok(t_minishell **msh);
bool		any_of_these_syn(const char *line);
bool		unsupported_operators(const char *line);
void		exec_fake_hd(const char *line, int hd_index);

//21_syntax_quotes.c
bool		unclosed_quotes(const char *line);

//22_syntax_pipes.c
bool		misplaced_pipe(const char *line);
bool		pipe_at_beginning(const char *line);
bool		pipe_at_end(const char *line);
bool		consec_operators_pipe(const char *line);

//23_syntax_redir.c
bool		conseq_operators_redir(const char *line);
void		conseq_redir_r_case(const char *line, int i);
void		conseq_redir_l_case(const char *line, int i);
bool		misplaced_redir_at_end(const char *line);

//24_syntax_utils.c
bool		look_for_pipe(const char *line, int i);
bool		check_in_quotes(char c, bool *in_quotes);
int 		check_if_hd(const char *line);
char		*get_eof(const char *line, int hd_index);

/************ 30_tokens ************/
//30_tokenizer.c
void		get_tokens(t_minishell **msh, int i, char quote_char);
bool		any_of_these_tk(t_minishell **msh, int *i, char c, bool in_quotes, char quote_char); //too many args
void		sub_tokenize(t_minishell **msh);
void		handle_filename(t_token_lst *token_list);
char		*check_env_cmd(char *cmd, char *env_path, int i);

//31_token_words.c
int			token_is_word(t_minishell **msh, int start);
int			token_is_word_in_quotes(t_minishell **msh, int start,
				bool *in_quotes, char *quote_char);
int			token_is_space(t_minishell **msh, int start);

//32_token_pipes_and_redir_r.c
int			token_is_pipe(t_minishell **msh, int start);
int			redir_r(t_minishell **msh, int start);
int			token_is_redir_app(t_minishell **msh, const char *line,
				char *redir_app, int i);
int			token_is_redir_out(t_minishell **msh, const char *line,
				char *redir_out, int i);

//33_token_redir_l.c
int			redir_l(t_minishell **msh, int start);
int			token_is_redir_hd(t_minishell **msh, const char *line,
				char *redir_hd, int i);
int			token_is_redir_in(t_minishell **msh, const char *line,
				char *redir_in, int i);

//34_token_utils.c
void		check_quote(bool *in_quotes, char *quote_char, char c);
void		append_token(t_minishell *msh, t_token_lst *new_token, char *content, t_token_type type);
char		*get_path(t_list *envp_list);
void 		check_double_cmd(t_minishell **msh);
/************ 40_build_tree ************/
//40_tokens_to_tree.c
void		parse_line(t_minishell **msh);
t_tree_node	*new_tree_node(t_token_type *type, char *content);

//41_build_pipe_nodes.c
t_tree_node	*build_pipe_node(t_token_lst **tokens);

//42_build_redir_nodes.c
t_tree_node	*build_redir_node(t_token_lst **token_list);
t_tree_node *handle_redir(t_tree_node *redir_node, t_token_lst **curr_token, bool *cmd_excep);
t_tree_node	*attach_redir(t_tree_node *redir_node, t_tree_node *new_redir);
bool		check_cmd(t_token_lst **token_list, bool cmd_excep);
t_tree_node	*add_leftmost(t_tree_node *redir_node, t_tree_node *cmd_node, bool cmd_excep);

//43_build_cmd_nodes.c
t_tree_node	*build_cmd_node(t_token_lst **token_list);
void		handle_cmd(t_tree_node *cmd_node, t_token_lst **curr_token, t_list **args);
char		**join_cmd_and_args(char *cmd, char **args);
t_list 		*reverse_args(t_list **head);

//44_tree_utils.c
t_token_lst	*safe_next_token(t_token_lst *curr_token);
bool		type_is_redir(t_token_type *type);
bool		type_is_word(t_token_type *type);
bool		type_is_cmd(t_token_type *type);
bool		type_is_arg(t_token_type *type);

/************ 50_built_ins ************/
int			print_work_dir(void);
int			print_env(t_minishell **msh, t_tree_node **node);
int			ft_echo(t_tree_node **node);

int			ft_cd(t_minishell **msh, t_tree_node **node);
int			get_dir(t_tree_node **node, char **target_dir);
int			update_cd_env(t_minishell **msh, char *old_pwd);
int			update_env_var(t_list **env_list, const char *var_name,
				const char *content);
void		add_new_env_var(t_list **env_list, const char *var_name,
				const char *data);

/************ 60_exec_tree ************/
//60_exec_tree.c
void		exec_tree(t_minishell **msh, t_tree_node *node);
void		exec_heredocs(t_tree_node *node);

//61_exec_pipe.c
void		exec_pipe(t_minishell **msh, t_tree_node *node);
void		perform_left_pipe(int useless_fd, int dup_fd, int curr_pid);
void		perform_right_pipe(int useless_fd, int dup_fd, int curr_pid);

//62_exec_redir.c
void		exec_redir_before_cmd(t_minishell **msh, t_tree_node *node);
int			exec_redir(t_tree_node *node);
int			create_file_fd(t_token_type type, char *file_name);
int			collect_redirs_and_cmd(t_tree_node **current_node, t_tree_node **redir_nodes, t_redir_data *redir_data);

//63_exec_heredoc.c
void	handle_hd(t_tree_node *node, int hd_fd);
char	*check_eof(t_tree_node *node, char *file_name);

//64_exec_cmd.c
void		exec_cmd(t_minishell **msh, t_tree_node *node);
void		exec_bt_cmd(t_minishell **msh, t_tree_node *node);
void		exec_env_cmd(t_minishell **msh, t_tree_node *node);

//65_exec_utils.c
int			safe_fork(void);
int			safe_dup(int old_fd, int curr_pid);
void 		safe_dup2(int new_fd, int old_fd, int curr_pid);
int			safe_pipe(int pipe_fd[2]);

/************ others ************/
//10_close_msh.c
void		close_minishell(t_minishell	*msh, int exit_code);
void		free_msh(t_minishell *msh);
void		handle_envp_failure(t_minishell *msh, char *str, t_list *list_node,
				char *array);
void		free_tokens(t_token_lst *token_list);
void		free_prompt_line(t_minishell **msh);
void		free_tree(t_tree_node *node);

//11_debug_utils.c
void		print_tokens(t_minishell **msh);
void		print_envp_in_struct(t_minishell **msh);
void		print_tree(t_tree_node *node);

#endif
