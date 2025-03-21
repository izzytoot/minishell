/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:50:18 by root              #+#    #+#             */
/*   Updated: 2025/03/21 18:35:56 by icunha-t         ###   ########.fr       */
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
# define ERR_MEM "Error allocating memory\n"
# define ERR_STDIN "Error with stdin\n"
# define ERR_PRC "Error creating process\n"
# define ERR_ENVP "Error duplicating environment variables\n"
# define ERR_SYN_EMPT "Command '' not found\n"
# define ERR_SYN_SQT "msh: syntax error - unclosed single quotes\n"
# define ERR_SYN_DQT "msh: syntax error - unclosed double quotes\n"
#define ERR_SYN_PIPE "msh: syntax error near unexpected token `|'\n"
#define ERR_SYN_REDIR_NL "msh: syntax error near unexpected token `newline'\n"
#define ERR_SYN_REDIR_HD "msh: syntax error near unexpected token `<<'\n"
#define ERR_SYN_REDIR_HD_OPEN "msh: syntax error heredoc open `<<'\n"
#define ERR_SYN_REDIR_IN "msh: syntax error near unexpected token `<'\n"
#define ERR_SYN_REDIR_OUT "msh: syntax error near unexpected token `>'\n"
#define ERR_SYN_REDIR_APP "msh: syntax error near unexpected token `>>'\n"
# define ERR_SYN_UNS_OP "msh: syntax error - unsupported operator\n"


//constants
#define WHITESPACE " \t\n\r\v\f"
#define OPERATOR "|<>"
#define REDIR "<>"
#define QUOTE "\"\'"
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

/*
typedef enum	e_node_type
{
	PIPE,
	EXEC,
	REDIR,
}	t_node_type;
*/

typedef enum	e_token_type
{
	PIPE, // |
	WORD, // cmd or arg
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

typedef struct s_minishell
{
	bool		active;
	char		*dir;
	int			msh_pid;
	char		*promt_line;
	t_token_lst	*token_list;
	char		**envp;
	t_list		*envp_list; //enviroment variables line user, home, path, etc
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

//12_init_utils.c
void		init_all_null (t_minishell **msh);
int			my_getpid(t_minishell *msh);

/************ 20_syntax ************/
//20_syntax_check.c
bool		syntax_is_ok(t_minishell **msh);
bool		hd_open(const char *line); // para remover quando resolvermos heredoc

//21_syntax_quotes_and_unsuported.c
bool		empty_quotes(const char *line);
bool 		unclosed_quotes(const char *line);
bool		unsupported_operators(const char *line);

//22_syntax_pipes.c
bool		misplaced_pipe(const char *line);
bool		pipe_at_beginning(const char *line);
bool		pipe_at_end(const char *line);
bool		consec_operators_pipe(const char *line);

//23_syntax_redir.c
bool		misplaced_redir_at_end(const char *line);
bool		conseq_operators_redir(const char *line);
void		conseq_redir_r_case(const char *line, int i);
void		conseq_redir_l_case(const char *line, int i);
bool		misplaced_redir_hd(const char *line);

//24_syntax_utils.c
bool		look_for_pipe(const char *line, int i);
bool		check_in_quotes(char c, bool *in_quotes);

/************ 30_tokens ************/
//30_tokenizer.c
void 		get_tokens(t_minishell **msh);
void		append_token(t_minishell *msh, t_token_lst *new_token, char *content, t_token_type type);
t_token_lst	*find_last_token(t_token_lst *token_list);

//31_token_type_p1.c
int			token_is_word(t_minishell **msh, int start);
int			token_is_pipe(t_minishell **msh, int start);
int			redir_r(t_minishell **msh, int start);
int			token_is_redir_app(t_minishell **msh, const char *line, char *redir_app, int i);
int			token_is_redir_out(t_minishell **msh, const char *line, char *redir_out, int i);

//32_token_type_p2.c
int			redir_l(t_minishell **msh, int start);
int			token_is_redir_hd(t_minishell **msh, const char *line, char *redir_hd, int i);
int			token_is_redir_in(t_minishell **msh, const char *line, char *redir_in, int i);

//33_token_utils.c
void		check_quote(bool *in_quotes, char *quote_char, char c);

/************ others ************/
//10_close_msh.c
void		close_minishell(t_minishell	*msh, char *err_msg, int exit_code);
void		free_msh(t_minishell *msh);
void		handle_envp_failure(t_minishell *msh, char *str, t_list *list_node, char *array);

//11_debug_utils.c
void		print_tokens(t_minishell **msh);
void		print_envp_in_struct(t_minishell **msh);

#endif


/*
typedef struct s_cmd
{
	t_token_type	type;
}	t_cmd;

typedef struct s_pipe_cmd // |
{
	t_token_type	type;
	t_cmd 			*left;
	t_cmd			*right;
}	t_pipe_cmd;

typedef struct	s_exec
{
	t_token_type	type;
	char			**s_av;
	char			**e_av;
}	t_exec;

typedef struct	s_red
{
	t_token_type	type;
	t_cmd			*r_cmd;
	char			*file;
	char			*e_file;
	int				fd_mode;
	int				fd;
	
}	t_red;
*/

//00_constructors.c
//t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right);
//t_cmd	*exec_cmd(void);
//t_cmd	*red_cmd(t_cmd *sub_cmd, char *file, char *e_file, int mode, int fd, t_token_type type);
