/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:50:18 by root              #+#    #+#             */
/*   Updated: 2025/06/12 16:51:50 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                  LIBRARIES                                 */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <string.h>
# include <stdlib.h>
# include <termios.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <errno.h>
# include <linux/limits.h>
# include <limits.h>
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
# define ERR_PT "msh: .: fn argument required\n.: usage: . fn [args]\n"
# define ERR_PID_EXP "msh: PID expansion unsupported\n"
# define ERR_HD_EOF "msh: warning: here-document delimited by end-of-file "
# define ERR_2FOLDER "cd: error retrieving current directory: getcwd: cannot "
# define ERR_2FD_2 "access parent directories: No such file or directory\n"
# define ERR_BIN "cannot access "

//constants
# define WS " \t\n\r\v\f"
# define OPERATOR "|<>"
# define NON_EOF "|<>&"
# define SYM_EXP ".,-+:/^&*!~=#?[]{}%\\"
# define REDIR "<>"
# define QT "\"\'"

/* ************************************************************************** */
/*                                   STRUCTS                                  */
/* ************************************************************************** */

typedef enum e_tk_type
{
	PIPE,
	WORD,
	BT_CMD,
	ARG,
	W_SPACE,
	FILE_NAME,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APP,
	REDIR_HD,
	ENV_CMD,
}	t_tk_type;

typedef struct s_quote
{
	bool			in_squotes;
	bool			in_dquotes;
	bool			in_quotes;
	bool			sp_case;
	char			quote_char;
	char			*content;
	bool			exp;
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
	bool				cmd_r;
	bool				ch_ambg;
	char				*eof;
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
	bool	ch_exp;
}	t_hd_lines;

typedef struct s_exp_cont
{
	char	*pre_c;
	char	*new_c;
	char	*post_c;
}	t_exp_cont;

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
	char		*prompt_line;
	t_tk_lst	*token_list;
	t_tree_nd	*tree_root;
	char		**envp;
	t_list		*envp_list;
	t_list		*vars_list;
	bool		debug_mode;
	bool		hd_check;
	char		*tmp_fname;
	bool		empties;
	bool		signal;
	t_list		*export_only;
	bool		child;
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
char			*get_prompt(t_msh *msh);
char			*get_display_path(t_msh *msh);
int				exit_value(t_msh **msh, int exit_code, int upd_exit, int close);

//11_envp_copies.c
void			copy_envp(t_msh *msh, char **envp);
char			**envp_to_array(t_msh *msh, char **envp);
void			envp_to_list(t_msh *msh, char **envp);
char			**cpy_for_execve(t_msh **msh);
void			env_i(t_list **env_list);

//12_init_utils.c
void			init_all_null(t_msh **msh);
bool			ch_shlvl(t_msh **msh, char *word);
char			*get_errmsg(void);
void			free_and_clear(char *str, t_list *lst);
bool			ch_shlvl_bin(t_msh **msh, char *word);

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
bool			check_l_and_r(const char *line, int i);
void			conseq_redir_r_case(const char *line, int i);
void			conseq_redir_l_case(const char *line, int i);
bool			misplaced_redir_at_end(const char *line);

//24_syntax_utils.c
bool			line_and_hd_index(t_msh **msh, const char **line,
					int *hd_index);
bool			look_for_pipe(const char *line, int i);
bool			check_in_quotes(char c, bool *in_quotes);
int				check_if_hd(const char *line);
char			*get_eof(const char *line, int hd_index);

/************ 30_tokens ************/
//30_tokenizer.c
void			get_tokens(t_msh **msh, int i);
void			init_qt_struct(t_quote *quotes);
bool			extra_check(t_msh **msh, int *i, char c, t_quote *quote);
int				exp_to_null(t_msh **msh, int start);
void			app_tk(t_msh *msh, t_tk_lst *new_tk,
					char *content, t_tk_type type);

//31_token_words.c
int				tk_word(t_msh **msh, int start);
int				tk_word_qt(t_msh **msh, int start,
					bool *in_quotes, char *quote_char);
int				tk_space(t_msh **msh, int start);
void			attr_qts(t_tk_lst *new_tk);

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
void			sort_out_quotes(t_msh **msh, const char *line, int *i,
					t_quote *quotes);
void			sort_quotes_util(t_msh **msh, int *i, const char *line,
					t_quote *quotes);
void			sort_empty_qt(t_msh **msh, t_quote *quotes);
void			check_dquote(bool *in_dquotes, char c);
void			check_squote(bool *in_squotes, char c);

//35_sub_tokenize.c
void			sub_tokenize(t_msh **msh);
void			join_rest(t_msh **msh);
void			join_rest_util(t_msh **msh, t_tk_lst *mg_tg, t_tk_lst *tmp_w);
void			rm_joined_tk(t_msh **msh, t_tk_lst **mg_tg,
					t_tk_lst **tmp_w, int n);
void			attribute_type(t_msh **msh, t_tk_lst *curr);

//36_sub_tokenize_files.c
void			handle_filename(t_msh **msh);
void			join_filename(t_msh **msh, bool hd_flag, t_tk_lst *tmp_fn);
t_tk_lst		*find_file(t_msh **msh, t_tk_lst *curr);
void			expand_fn(t_msh **msh, t_tk_lst **tmp_fn,
					t_tk_lst **merge_tg, bool hd_flag);
char			*check_env_cmd(char *cmd, char *env_path, int i, int n);

//37_sub_tokenize_utils.c
bool			look_for_exp(t_tk_lst *curr, char *word);
char			*check_env_cmd(char *cmd, char *env_path, int i, int n);
void			get_cmd_path(char	*path, char	**part_path,
					char **cmd_path, char *cmd);
void			join_parts(t_tk_lst	**src, t_tk_lst **target);
t_tk_lst		*find_w_tk(t_msh **msh);

//38_token_utils.c
bool			tk_in_qts(t_tk_lst *tk);
char			*get_path(t_list *envp_list);
void			check_rep_cmd(t_msh **msh);
bool			check_builtin(char *str);
bool			check_shell_var(char *str);

/************ 40_empties ************/
//40_empties.c
int				empty_case(t_msh **msh, const char *line, int i, bool flag);
int				ch_empty_case(t_msh **msh, const char *line, int i, bool fl);
int				sp_for_empty_case(t_msh **msh, const char *line, int i, int n);
int				ch_emp_exp(t_msh **msh, char *nl);
int				ch_all_same(char *nl);

//41_rm_empties.c
void			rm_empties(t_tk_lst **token);
void			empties_rmv_exp(t_tk_lst ***curr);
void			empties_rmv_tk(t_tk_lst ***curr);
void			empties_rmv_tk_util(t_tk_lst ****curr);
void			empties_rmv_doll(t_tk_lst ***tk);

//42_empties_utils.c
bool			emp_1(char *nl, const char *line, int tmp_i);
bool			emp_2(char *nl, bool fl);
void			first_and_pipe(t_tk_lst ***curr_f, t_tk_lst *curr_p, bool *env);
void			rm_empties_case(t_tk_lst **curr, bool env);
void			rest_of_word(char *nl, const char *line, int i);

/************ 50_build_tree ************/
//50_tokens_to_tree.c
void			parse_line(t_msh **msh);
t_tree_nd		*new_tree_nd(t_tk_lst *curr_tk, t_tk_type *type, char *content);
void			new_tree_nd_util(t_tree_nd	*new_nd);
void			add_quote_structs(t_tree_nd *new_nd, t_tk_lst *token);
void			app_qt(t_tree_nd *new_nd, t_tk_lst *token);

//51_build_pipe__nodes.c
t_tree_nd		*build_pipe_nd(t_msh **msh, t_tk_lst **tokens);
void			bd_pp_nd_util(t_tk_lst	**n_tk, t_tk_lst **c_tk,
					t_tk_lst **l_tk, t_tk_lst **p_tk);
void			move_fwd(t_tk_lst **prev_tk, t_tk_lst **curr_tk);

//52_build_redir_nodes.c
t_tree_nd		*build_redir_nd(t_msh **msh, t_tk_lst **token_list);
t_tree_nd		*handle_redir(t_msh **msh, t_tree_nd *redir_nd,
					t_tk_lst **curr_tk);
bool			check_cmd(t_tk_lst **token_list);
bool			search_cmd(t_tk_lst *curr_tk, int way);

//53_build_redir_nodes_utils.c
bool			next_is_redir(t_tk_lst *curr_tk);
bool			check_prev(t_tk_lst *curr_tk);
t_tree_nd		*add_left(t_tree_nd *redir_nd, t_tree_nd *cmd_nd);
t_tree_nd		*attach_redir(t_tree_nd *redir_nd, t_tree_nd *new_redir);

//54_build_cmd_nodes.c
t_tree_nd		*build_cmd_nd(t_msh **msh, t_tk_lst **token_list);
void			handle_cmd(t_msh **msh, t_tree_nd *cmd_nd, t_tk_lst **curr_tk,
					t_list **args);
char			**join_cmd_and_args(char *cmd, char **args);
char			*ch_env_cont(t_list *envp_list, t_list *vars_list,
					char *key_word);

//55_type_is_utils.c
bool			type_is_redir(t_tk_type *type);
bool			type_is_word(t_tk_type *type);
bool			type_is_cmd(t_tk_type *type);
bool			type_is_arg(t_tk_type *type);

//56_tree_utils.c
t_tk_lst		*safe_next_tk(t_tk_lst *curr_tk);
t_tk_lst		*safe_prev_tk(t_tk_lst *curr_tk);
void			add_fname(t_msh **msh, t_tree_nd *new_redir, t_tk_lst *curr_tk);
t_list			*reverse_args(t_list **head);
void			ch_ambg(t_msh **msh, t_tree_nd *new_redir, char *fname,
					t_tk_lst *tk);

/************ 60_built_ins ************/
//60_pwd.c
int				ft_pwd(void);

//61_cd.c
int				ft_cd(t_msh **msh, t_tree_nd **node);
int				get_dir(t_msh **msh, t_tree_nd **node, char **target_dir);
int				update_cd_env(t_msh **msh, char *old_pwd);
int				update_cd_var(t_list **env_list, const char *var_name,
					const char *data);
char			*safe_getcwd(t_msh *msh, bool silent);

//62_env.c
int				print_env(t_msh **msh, t_tree_nd **node);
int				update_var(t_list **env_list, const char *var_name,
					const char *content);
int				add_new_var(t_list **env_list, const char *var_name,
					const char *data);
char			*get_var_val(t_list *env_list, const char *var_name);
char			*update_var_util(const char *var_name, const char *data);

//63_echo.c
int				ft_echo(t_tree_nd **node);
bool			handle_n(t_tree_nd **node, int *i, bool first_flag);
bool			get_newline(bool first_flag, bool *newline);

//64_exit.c
int				ft_exit(t_msh **msh, t_tree_nd **node);	
unsigned int	ft_convert_value(t_msh **msh, char *code);
int				ft_strnumeric(char *str);
void			get_ex_code(t_msh **msh, unsigned char	*exit_code,
					char **args);

//65_unset.c
int				ft_unset(t_msh **msh, t_tree_nd **node);
void			ft_delete_env_var(t_list **env_list, const char *var_name);
void			ft_del_export_only(t_list **export_only, const char *var_name);
void			ft_del_vars_list(t_list **vars_list, const char *var_name);

//66_export.c
int				ft_export(t_msh **msh, t_tree_nd **node, int i,
					int valid_export);
t_list			*sort_env(t_list *env_list, int sort);
void			disp_exported(t_msh **msh, int name_len);
t_list			*copy_env_list(t_list *env_list);
void			print_only_export(t_msh	*msh);

//67_export_utils.c
bool			is_valid_identifier(char *arg, t_quote *tmp_lst);
bool			export_check(t_msh **msh, t_quote **tmp_lst, char *arg);
void			add_export_var(t_list **env_list, const char *var_name,
					const char *data);
bool			sing_exp(char *arg);
void			add_only_to_export(t_msh *msh, const char *var_name);

//68_export_utils_2.c
void			ft_export_util(t_msh **msh, bool s_qt, char *arg,
					char	**var_inf);
void			get_var_info(t_tree_nd **node, t_quote *tmp_lst, int i,
					char ***var_inf);
void			move_on(int *i, t_quote **tmp_lst);

/************ 70_exec_tree ************/
//70_exec_tree.c
int				exec_tree(t_msh **msh, t_tree_nd *node);
char			**remake_args(t_tree_nd *node);
void			sub_cmd(t_msh **msh, t_tree_nd *node, char ***new_args);
void			sub_cmd_util(t_tree_nd *node, char **sep_args, int count,
					char ****new_args);
int				deal_with_hd(t_msh **msh, t_tree_nd *node, int status);
//71_exec_pipe.c
int				exec_pipe(t_msh **msh, t_tree_nd *node);
void			perf_left_pipe(t_msh **msh, int useless_fd, int dup_fd);
void			perf_right_pipe(t_msh **msh, int useless_fd, int dup_fd);
int				safe_waitpid(int pid1, int pid2);
void			close_fd(int fd_1, int fd_2);

//72_exec_redir.c
int				exec_redir_before_cmd(t_msh **msh, t_tree_nd *node);
int				collect_redirs_and_cmd(t_msh **msh, t_tree_nd **curr_nd,
					t_tree_nd **redir_nd, t_redir_data *redir_data);
int				exec_redir(t_msh **msh, t_tree_nd *node);
int				create_file_fd(t_tk_type type, char *file_name);
void			init_str_reset_std(t_msh **msh, t_redir_data *redir_data,
					int n);

//73_exec_heredoc.c
void			exec_heredocs(t_msh **msh, t_tree_nd *node);
void			handle_hd(t_msh **msh, t_tree_nd *node, int hd_fd);
char			*check_eof(t_tree_nd *node, char *file_name);
void			exec_files(t_msh **msh, t_tree_nd *node);
void			save_lines(t_msh **msh, t_hd_lines lines, t_tree_nd	*curr_nd,
					int hd_fd);

//74_exec_cmd.c
int				exec_cmd(t_msh **msh, t_tree_nd *node);
int				exec_bt_cmd(t_msh **msh, t_tree_nd *node);
int				exec_env_cmd(t_msh **msh, t_tree_nd *node);
int				exec_sh_v(t_msh **msh, t_tree_nd *node);
int				safe_execve(t_msh **msh, char *path, char **argv);

//75_remake_args_utils.c
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

//76_exec_dir_path.c
int				choose_path(t_msh **msh, t_tree_nd *node, char **path);
int				direct_path(t_tree_nd *node);
int				is_direct_command(t_tree_nd *node);
int				handle_direct_command(t_msh **msh, t_tree_nd *node,
					char **path);
int				handle_no_path(t_msh **msh, t_tree_nd *node);

//77_exec_utils.c
int				safe_fork(t_msh **msh);
int				safe_dup(t_msh **msh, int old_fd);
void			safe_dup2(t_msh **msh, int new_fd, int old_fd);
int				safe_pipe(t_msh **msh, int pipe_fd[2]);
void			update_shlvl(t_list **env_list);

//78_exec_utils_2.c
bool			arg_expansions(t_tree_nd *node);
bool			ch_if_sub_cmd(t_msh **msh, t_tree_nd *node);
int				output_cmd_errors(t_msh **msh, t_tree_nd *node);
char			**get_joinned_array(char *tmp_cmd, char **sep_args_tmp,
					char ****new_args);

//79_exec_cmd_utils.c
void			deal_with_cmd(t_msh **msh, t_tree_nd *node, int *status);
void			exec_cmd_child(t_msh **msh, t_tree_nd *node, int *status);
void			exec_cmd_parent(pid_t pid, int *status);

//79_1_exec_pipe_utils.c
void			pipe_right_child(t_msh **msh, t_tree_nd *node, int *status,
					int *fd);
int				pid2_handler(int pid2, int status);

/************ 80_expander ************/
//80_expand_args.c
void			expand_args(t_msh **msh, t_tree_nd *node);
void			expand_loop(t_msh **msh, t_tree_nd *node, char **args_cpy);
void			expander(t_msh **msh, t_tree_nd **node, char **arg);
void			expand_tk(t_msh **msh, char **arg);
void			subst_arg(char **arg, t_exp_cont *parts);

//81_expand_fname.c
void			expand_fname(t_msh **msh, char **fname);
void			subst_fname(char **fname, t_exp_cont *parts);
void			expand_and_join_fname(t_msh **msh, t_tk_lst *tmp_fn,
					t_tk_lst *merge_tg, bool hd_flag);
//82_expand_hd.c
void			expand_line(t_msh **msh, t_hd_lines *lines,
					t_tree_nd *curr_nd, int hd_fd);
char			*expand_word(t_msh **msh, char *word);
char			*get_pre_cont_hd(char *arg, int *i);
int				len_pre_cont_hd(char *arg, int i);
int				wr_pre_cont_hd(char *arg, char **pre_content, int i, int len);

//83_build_kw_lst.c 
void			build_kw_list(t_kw **kw_lst, char *arg, int *i);
void			get_exp_kw(int next, t_kw *n_kw, char *arg, int *i);
char			*get_util(char *arg, int **i, int n);
void			app_kw(t_kw **kw_lst, t_kw *new_kw, char *kw, bool exp);
bool			check_dollar_w_qts(char **str);

//84_expand_key_words.c
void			expand_kw(t_msh **msh, t_kw **kw_lst);
bool			other_expand_cases(t_msh **msh, char **kw);
int				expand_case(char *kw);
char			*get_env_cont(t_list *envp_list, t_list *vars_list,
					char *key_word);
char			*find_env_value(t_list *list, char *key_word, int key_len);

//85_get_parts.c
char			*get_pre_cont(char *arg, int *i);
char			*get_key_word(char *arg, int *i);
char			*get_mid_cont(char *arg, int *i);
char			*get_mid_cont_w_sp(char *arg, int *i);
char			*get_post_cont(char *arg, int *i);

//86_final_expander.c
char			*get_exp_cont(t_kw **kw_lst);
char			*get_final_cont(t_exp_cont *parts);
void			get_final_cont_util(char **tmp_new_c, char **final_c,
					t_exp_cont *parts);
char			*get_tmp(char *new_c, char *post_c, int len);
char			*ultimate_joint(char *pre_c, char *tmp);

//87_expand_utils.c
void			recurs_exp_args(t_msh **msh, t_tree_nd *node);
int				get_kw_len(char *arg, int **i, int tmp_i, bool *flag);
bool			check_mid(char c);
int				count_exp(char *arg, int i);

//88_expand_utils_2.c
char			**ft_array_dup_null(t_tree_nd *node, char **array, int n);
char			**copy_array(int size, char **array);

/************ 90_signals ************/
//90_signals.c
void			sig_c_main(int sig);
void			ctrl_c_hd(int sig);
void			sig_c_child(int sig);
void			sig_ig(int sig);
void			start_sigs(void);

//91_signals_utils.c
t_msh			*get_msh(t_msh *msh, int flag);
void			close_fds(void);
void			ctrl_d_error(char *eof);
void			sig_cmd_child(void);

/************ 100_close_and_free ************/
//100_free_msh.c
void			free_msh(t_msh *msh);
void			free_prompt_line(t_msh **msh);
void			free_tree(t_msh *msh, t_tree_nd *node);

//101_close_msh.c
void			close_minishell(t_msh	*msh, int exit_code);
void			envp_fail(t_msh *msh, char *str, t_list *list_nd,
					char **array);
void			close_msh_prompt(t_msh **msh);

//102_other_frees.c
void			free_tokens(t_tk_lst *token_list, int n);
void			free_qt_lst(t_quote *qt_list);
void			free_kw_structs(t_exp_cont *parts, t_kw **kw_lst);

/************ others ************/
//11_debug_utils.c
void			print_tokens(t_msh **msh);
void			print_envp_in_struct(t_msh **msh);
void			print_tree(t_tree_nd *node);

#endif
