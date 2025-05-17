/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:50:18 by root              #+#    #+#             */
/*   Updated: 2025/05/17 12:50:45 by ddo-carm         ###   ########.fr       */
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
# define ERR_DIRNOTFOUND "No such file or directory\n"
# define ERR_AMBREDIR "ambiguous redirect\n"
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
# define ERR_KW "msh: too many keywords for expander\n"

//constants
# define WS " \t\n\r\v\f"
# define OPERATOR "|<>"
# define NON_EOF "|<>&" //check if there are more
# define SYM_EXP ".,-+:/@^&*!~=#?[]{}%"
# define REDIR "<>"
# define QT "\"\'"
# define MAX_KW 128
/* ************************************************************************** */
/*                                   STRUCTS                                  */
/* ************************************************************************** */

typedef enum e_cmd_type
{
	ECH,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
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
	SH_V, //shell var
}	t_tk_type;

typedef struct s_quote
{
	bool			in_squotes;
	bool			in_dquotes;
	bool			in_quotes;
	bool			space_case;
	char			quote_char;
	char			*content;
	struct s_quote	*next;
	struct s_quote	*prev;
}	t_quote;

typedef struct s_tk_lst
{
	t_tk_type				type;
	char					*content;
	struct s_tk_lst			*next;
	struct s_tk_lst			*prev;
	struct s_quote			quotes;
}	t_tk_lst;

typedef struct s_tree_nd
{
	t_tk_type			type;
	char				*op_content;
	char				**cmd_content;
	bool				eof_ch;
	char				**args;
	char				*cmd;
	int					nb_arg;
	t_tk_type			cmd_type;
	char				*file;
	char				*tmp_file;
	int					fd;
	struct s_tree_nd	*left;
	struct s_tree_nd	*right;
	struct s_quote		*quote_lst;
	bool				exp_hd;
}	t_tree_nd;

typedef struct s_redir_data
{
	int			orig_stdin;
	int			orig_stdout;
	t_tree_nd	*cmd_nd;
}	t_redir_data;

typedef struct s_flag_str
{
	bool	written;
	bool	space_prev;
	bool	space_next;
}	t_flag_str;

typedef struct s_ints
{
	int		i;
	int		j;
}	t_ints;

typedef struct s_hd_lines
{
	char	*new_l;
	char	**exp_newl;
}	t_hd_lines;

typedef struct s_exp_cont
{
	char	*pre_c;
	char	*new_c;
	char	*post_c;
} t_exp_cont;

typedef struct s_kw
{
	char		*kw;
	struct s_kw	*next;
	struct s_kw	*prev;
	bool		exp;
}	t_kw;

typedef struct s_msh
{
	bool		active;
	char		*dir;
	int			msh_pid;
	char		*prompt_line;
	t_tk_lst	*token_list;
	t_tree_nd	*tree_root;
	char		**envp;
	t_list		*envp_list; //enviroment variables line user, home, path, etc
	t_list		*vars_list;
	bool		debug_mode;
	bool		hd_check;
	char		*tmp_fname;
}	t_msh;

/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */

/************ 00_main ************/
//00_main.c
int				main(int ac, char **av, char **envp);

/************ 10_init ************/
//10_init_msh.c
void			ft_init_msh(t_msh **msh, char **envp);
void			prompt_and_read(t_msh **msh);
char			*get_prompt(void);
int				exit_value(t_msh **msh, int exit_code, int upd_exit, int close);
//11_envp_copies.c
void			copy_envp(t_msh *msh, char **envp);
char			**envp_to_array(t_msh *msh, char **envp);
void			envp_to_list(t_msh *msh, char **envp);
char			**cpy_for_execve(t_msh **msh);

//12_init_utils.c
void			init_all_null(t_msh **msh);

/************ 20_syntax ************/
//20_syntax_check.c
int				syntax_is_ok(t_msh **msh);
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
void			init_qt_struct(t_quote *quotes);
bool			extra_check(t_msh **msh, int *i, char c, t_quote *quote);

//31_token_words.c
int				tk_word(t_msh **msh, int start);
int				tk_word_qt(t_msh **msh, int start,
					bool *in_quotes, char *quote_char);
int				tk_space(t_msh **msh, int start);

//32_token_pipes_and_redir_r.c
int				tk_pipe(t_msh **msh, int start);
int				redir_r(t_msh **msh, int start);
int				tk_redir_app(t_msh **msh, const char *line,
					char *redir_app, int i);
int				tk_redir_out(t_msh **msh, const char *line,
					char *redir_out, int i);

//33_token_redir_l.c
int				redir_l(t_msh **msh, int start);
int				tk_redir_hd(t_msh **msh, const char *line,
					char *redir_hd, int i);
int				tk_redir_in(t_msh **msh, const char *line,
					char *redir_in, int i);

//34_handle_quotes.c
void			sort_out_quotes(int *i, const char *line, t_quote *quotes);
void			check_dquote(bool *in_dquotes, char c);
void			check_squote(bool *in_squotes, char c);

//35_sub_tokenize.c
void			sub_tokenize(t_msh **msh);
void			handle_filename(t_msh **msh);
void			join_filename(t_msh **msh, bool hd_flag);
void			join_rest(t_msh **msh);
char			*check_env_cmd(char *cmd, char *env_path, int i);

//36_sub_tokenize_utils.c
t_tk_lst		*find_file(t_msh **msh);
t_tk_lst		*find_w_tk(t_msh **msh);
void			join_parts(t_tk_lst	**src, t_tk_lst **target);
bool			ch_shlvl(char *word);
void			expand_fn(t_msh **msh, t_tk_lst **tmp_fn,
					t_tk_lst **merge_tg, bool hd_flag);

//37_token_utils.c
void			app_tk(t_msh *msh, t_tk_lst *new_tk,
					char *content, t_tk_type type);
char			*get_path(t_list *envp_list);
void			check_rep_cmd(t_msh **msh);
bool			check_builtin(char *str);
bool			check_shell_var(char *str);

//38_token_empties.c
void			empty_case(t_msh **msh, const char *line, int i, bool flag);
bool 			ch_all_same(char *nl);
int				exp_to_null(t_msh **msh, int start);
void			rm_empties(t_tk_lst **curr);

/************ 40_build_tree ************/
//40_tokens_to_tree.c
void			parse_line(t_msh **msh);
t_tree_nd		*new_tree_nd(t_tk_lst *curr_tk, t_tk_type *type, char *content);
void			add_quote_structs(t_tree_nd *new_nd, t_tk_lst *token);
void			app_qt(t_tree_nd *new_nd, t_tk_lst *token);

//41_build_pipe__nodes.c
t_tree_nd		*build_pipe_nd(t_tk_lst **tokens);

//42_build_redir_nodes.c
t_tree_nd		*build_redir_nd(t_tk_lst **token_list);
t_tree_nd		*handle_redir(t_tree_nd *redir_nd, t_tk_lst **curr_tk,
					bool *cmd_exc);
t_tree_nd		*attach_redir(t_tree_nd *redir_nd, t_tree_nd *new_redir);
bool			check_cmd(t_tk_lst **token_list, bool cmd_exc);
bool			search_cmd(t_tk_lst *curr_tk);

//43_build_cmd_nodes.c
t_tree_nd		*build_cmd_nd(t_tk_lst **token_list);
void			handle_cmd(t_tree_nd *cmd_nd, t_tk_lst **curr_tk,
					t_list **args);
char			**join_cmd_and_args(char *cmd, char **args);

//44_type_is_utils.c
bool			type_is_redir(t_tk_type *type);
bool			type_is_word(t_tk_type *type);
bool			type_is_cmd(t_tk_type *type);
bool			type_is_arg(t_tk_type *type);

//45_tree_utils.c
t_tk_lst		*safe_next_tk(t_tk_lst *curr_tk);
void			add_fname(t_tree_nd *new_redir, t_tk_lst *curr_tk);
bool			check_prev(t_tk_lst *curr_tk);
t_tree_nd		*add_left(t_tree_nd *redir_nd, t_tree_nd *cmd_nd, bool cmd_exc);
t_list			*reverse_args(t_list **head);

/************ 50_built_ins ************/
//50_pwd.c
int				ft_pwd(void);

//51_cd.c
int				ft_cd(t_msh **msh, t_tree_nd **node);
int				get_dir(t_msh **msh, t_tree_nd **node, char **target_dir);
int				update_cd_env(t_msh **msh, char *old_pwd);
int				update_cd_var(t_list **env_list, const char *var_name,
					const char *data);

//52_env.c
int				print_env(t_msh **msh, t_tree_nd **node);
int				update_var(t_list **env_list, const char *var_name,
					const char *content);
void			add_new_var(t_list **env_list, const char *var_name,
					const char *data);
char			*get_var_val(t_list *env_list, const char *var_name);

//53_echo.c
int				ft_echo(t_tree_nd **node);
bool			handle_n(t_tree_nd **node, int *i, bool first_flag);

//54_exit.c
int				ft_exit(t_msh **msh, t_tree_nd **node);	
unsigned int	ft_convert_value(t_msh **msh, char *code);
int				ft_strnumeric(char *str);

//55_unset.c
int				ft_unset(t_msh **msh, t_tree_nd **node);
void			ft_delete_var(t_list **env_list, const char *var_name);

//56_export.c
int				ft_export(t_msh **msh, t_tree_nd **node);
t_list			*sort_env(t_list *env_list, int sort);
void			disp_exported(t_msh **msh);
t_list			*copy_env_list(t_list *env_list);
char			*escape_value(char *value, int i, int j);

//57_export_utils.c
bool			is_valid_identifier(char *arg);
bool			export_check(t_msh **msh, char *arg);

/************ 60_exec_tree ************/
//60_exec_tree.c
int				exec_tree(t_msh **msh, t_tree_nd *node);
char			**remake_args(t_tree_nd *node);

//61_exec_pipe.c
int				exec_pipe(t_msh **msh, t_tree_nd *node);
void			perf_left_pipe(t_msh **msh, int useless_fd, int dup_fd,
					int curr_pid);
void			perf_right_pipe(t_msh **msh, int useless_fd, int dup_fd,
					int curr_pid);
int				safe_waitpid(int pid1, int pid2);
void			close_fd(int fd_1, int fd_2);

//62_exec_redir.c
int				exec_redir_before_cmd(t_msh **msh, t_tree_nd *node);
int				collect_redirs_and_cmd(t_msh **msh, t_tree_nd **curr_nd,
					t_tree_nd **redir_nd, t_redir_data *redir_data);
int				exec_redir(t_msh **msh, t_tree_nd *node);
int				create_file_fd(t_tk_type type, char *file_name);

//63_exec_heredoc.c
void			exec_heredocs(t_msh **msh, t_tree_nd *node);
void			handle_hd(t_msh **msh, t_tree_nd *node, int hd_fd);
char			*check_eof(t_tree_nd *node, char *file_name);

//64_exec_cmd.c
int				exec_cmd(t_msh **msh, t_tree_nd *node);
int				exec_bt_cmd(t_msh **msh, t_tree_nd *node);
int				exec_env_cmd(t_msh **msh, t_tree_nd *node);
int				exec_sh_v(t_msh **msh, t_tree_nd *node);
int				safe_execve(t_msh **msh, char *path, char **argv);

//65_remake_args_utils.c
void			init_aux_structs(t_flag_str *flags, t_ints *ints,
					t_tree_nd *node);
void			compose_arg(t_ints *ints, t_flag_str *flags,
					char **new_args, t_tree_nd *node);
void			add_last(t_ints *ints, t_flag_str *flags,
					char **new_args, t_tree_nd *node);
void			lonely_arg(t_ints *ints, t_flag_str *flags,
					char **new_args, t_tree_nd **node);
void			handle_written(t_ints *ints, t_flag_str *flags,
					t_tree_nd **node);

//66_exec_utils.c
int				safe_fork(t_msh **msh);
int				safe_dup(t_msh **msh, int old_fd, int curr_pid);
void			safe_dup2(t_msh **msh, int new_fd, int old_fd, int curr_pid);
int				safe_pipe(t_msh **msh, int pipe_fd[2]);
void			update_shlvl(t_list **env_list);

//67_exec_dir_path.c
int				choose_path(t_msh **msh, t_tree_nd *node, char **path);
int				direct_path(t_msh **msh, t_tree_nd *node);

/************ 70_expander ************/

//70_expand_args.c
void			expand_args(t_msh **msh, t_tree_nd *node);
void			expander(t_msh **msh, t_tree_nd **node, char **arg);
void			expand_tk(t_msh **msh, char **arg);
void			subst_arg(char **arg, t_exp_cont *parts);
char			**ft_array_dup_w_null(t_tree_nd *node, char **array, int n);

//71_expand_fname.c
void			expand_fname(t_msh **msh, char **fname);
void			subst_fname(char **fname, t_exp_cont *parts);

//72_expand_hd.c
void			expand_line(t_msh **msh, t_hd_lines *lines,
					t_tree_nd *curr_nd, int hd_fd);
char			*expand_word(t_msh **msh, char *word);

//73_build_kw_lst.c 
void			build_kw_list(t_kw **kw_lst, char *arg, int *i);
void			get_exp_kw(int next, t_kw *n_kw, char *arg, int *i);
char			*get_util(char *arg, int **i, int n);
void			app_kw(t_kw **kw_lst, t_kw *new_kw, char *kw, bool exp);

//74_expand_key_words.c
void			expand_kw(t_msh **msh, t_kw **kw_lst);
int				expand_case(char *kw);
char 			*get_env_cont(t_list *envp_list,  t_list *vars_list, char *key_word);

//75_get_parts.c
char			*get_pre_cont(char *arg, int *i);
char			*get_key_word(char *arg, int *i);
char			*get_mid_cont(char *arg, int *i);
char			*get_mid_cont_w_sp(char *arg, int *i);
char			*get_post_cont(char *arg, int *i);

//76_final_expander.c
char			*get_exp_cont(t_kw **kw_lst);
char			*get_final_cont(t_exp_cont *parts);
char			*get_tmp(char *new_c, char *post_c, int len);
char			*ultimate_joint(char *pre_c, char *tmp);

//77_expand_utils.c
void			recurs_exp_args(t_msh **msh, t_tree_nd *node);
int				get_kw_len(char *arg, int **i, int tmp_i, bool *flag);
bool			check_mid(char c);
int				count_exp(char *arg, int i);
char			**copy_array(int size, char **array);

/************ 80_close_and_free ************/
//80_free_msh.c
void			free_msh(t_msh *msh);
void			free_prompt_line(t_msh **msh);
void			free_tree(t_tree_nd *node);

//81_close_msh.c
void			close_minishell(t_msh	*msh, int exit_code);
void			envp_fail(t_msh *msh, char *str, t_list *list_nd, char *array);

//82_other_frees.c
void 			kw_err(void);
void			ft_free_str_arr(char **array); //check if needed
void			free_tokens(t_tk_lst *token_list);
void			free_qt_lst(t_quote *qt_list);
void			free_kw_structs(t_exp_cont *parts, t_kw **kw_lst);

/************ others ************/
//11_debug_utils.c
void			print_tokens(t_msh **msh);
void			print_envp_in_struct(t_msh **msh);
void			print_tree(t_tree_nd *node);

#endif
