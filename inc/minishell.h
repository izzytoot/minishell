/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:50:18 by root              #+#    #+#             */
/*   Updated: 2025/03/26 18:19:17 by ddo-carm         ###   ########.fr       */
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
# define ERR_CD_MANY_ARGS "bash: cd: too many arguments\n"

//constants
# define WHITESPACE " \t\n\r\v\f"
# define OPERATOR "|<>"
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


typedef enum	e_token_type
{
	PIPE, // |
	WORD, // cmd or arg
	W_CMD,
	W_ARG,
	W_SPACE,
	FILE_NAME,
	REDIR_IN, // < (input)
	REDIR_OUT, // > (output)
	REDIR_APP, // >> (append)
	REDIR_HD, // << (heredoc)
	ENV_VAR, // envirm. variables
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
    char				**args;
	char				*file; //for redirections
    int					fd;
	struct s_tree_node	*left;
    struct s_tree_node	*right;
}   t_tree_node;

typedef struct s_minishell
{
	bool		active;
	char		*dir;
	int			msh_pid;
	char		*promt_line;
	t_token_lst	*token_list;
	char		**envp;
	t_list		*envp_list; //enviroment variables line user, home, path, etc
	t_tree_node *tree_root;
	bool		debug_mode;
}	t_minishell;

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

//11_envp_copies.c
void		copy_envp(t_minishell *msh, char **envp);
char		**envp_to_array(t_minishell *msh, char **envp);
void		envp_to_list(t_minishell *msh, char **envp);
char 		*add_envp_newline(char *envp);

//12_init_utils.c
void		init_all_null (t_minishell **msh);
int			my_getpid(t_minishell *msh);

/************ 20_syntax ************/
//20_syntax_check.c
bool		syntax_is_ok(t_minishell **msh);
bool		hd_open(const char *line); // para remover quando resolvermos heredoc
bool		unsupported_operators(const char *line);

//21_syntax_quotes.c
bool 		unclosed_quotes(const char *line);
bool		empty_quotes(const char *line);

//22_syntax_pipes.c
bool		misplaced_pipe(const char *line);
bool		pipe_at_beginning(const char *line);
bool		pipe_at_end(const char *line);
bool		consec_operators_pipe(const char *line);

//23_syntax_redir.c
bool		conseq_operators_redir(const char *line);
void		conseq_redir_r_case(const char *line, int i);
void		conseq_redir_l_case(const char *line, int i);
bool		misplaced_redir_hd(const char *line);
bool		misplaced_redir_at_end(const char *line);

//24_syntax_utils.c
bool		look_for_pipe(const char *line, int i);
bool		check_in_quotes(char c, bool *in_quotes);

/************ 30_tokens ************/
//30_tokenizer.c
void		get_tokens(t_minishell **msh, int i, char quote_char);
bool		any_of_these(t_minishell **msh, int *i, char c, bool in_quotes, char quote_char);
void		change_filename_type(t_token_lst *token_list);

//31_token_words.c
int			token_is_word(t_minishell **msh, int start);
int			token_is_word_in_quotes(t_minishell **msh, int start, bool *in_quotes, char *quote_char);
int 		token_is_space(t_minishell **msh, int start);

//32_token_pipes_and_redir_r.c
int			token_is_pipe(t_minishell **msh, int start);
int			redir_r(t_minishell **msh, int start);
int			token_is_redir_app(t_minishell **msh, const char *line, char *redir_app, int i);
int			token_is_redir_out(t_minishell **msh, const char *line, char *redir_out, int i);

//33_token_redir_l.c
int			redir_l(t_minishell **msh, int start);
int			token_is_redir_hd(t_minishell **msh, const char *line, char *redir_hd, int i);
int			token_is_redir_in(t_minishell **msh, const char *line, char *redir_in, int i);

//34_token_utils.c
void		check_quote(bool *in_quotes, char *quote_char, char c);
void		append_token(t_minishell *msh, t_token_lst *new_token, char *content, t_token_type type);

/************ 40_parsing ************/
//40_parse_tokens.c
void		parse_line(t_minishell **msh);
t_tree_node *build_tree(t_token_lst **tokens);
t_tree_node *build_cmd_or_redir_node(t_token_lst **token_list);
void 		handle_redir(t_tree_node *redir_node, t_token_lst *current_token);

//41_parse_utils.c
t_tree_node *new_tree_node(t_token_type *type);
char 		**conv_list_to_array(t_list *list);
char		**ft_arraydup(char **array);

/************ 50_built_ins ************/
void		print_work_dir(void);
int			print_env(t_minishell **msh);
void		ft_echo(t_minishell **msh);

int	ft_cd(t_minishell **msh);
int execute_cd(t_minishell **msh, char *path);
int update_dir(char *old_dir, t_list **envp);
void	update_env_var(char *var_name, char *new_data, t_list *envp);

/************ others ************/
//10_close_msh.c
void		close_minishell(t_minishell	*msh, int exit_code);
void		free_msh(t_minishell *msh);
void		handle_envp_failure(t_minishell *msh, char *str, t_list *list_node, char *array);

//11_debug_utils.c
void		print_tokens(t_minishell **msh);
void		print_envp_in_struct(t_minishell **msh);
void		print_tree(t_tree_node *node);

#endif
