/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:50:18 by root              #+#    #+#             */
/*   Updated: 2025/03/17 11:35:49 by icunha-t         ###   ########.fr       */
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
# define GR "\033[0;32m"  
# define YLL "\033[0;33m" 
# define RES "\033[0m"
//error messages
# define ERR_MEM "Error allocating memory\n"
# define ERR_STDIN "Error with stdin\n"
# define ERR_PRC "Error creating process\n"
# define ERR_ENVP "Error duplicating environment variables\n"
//constants
#define WHITESPACE " \t\n\r\v\f"
#define TOKENS "|<>"
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
	char		*prog_name;
	t_token_lst	*token_list;
	t_list		*l_envp; //enviroment variables line user, home, path, etc
}	t_minishell;

/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */
//00_constructors.c
//t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right);
//t_cmd	*exec_cmd(void);
//t_cmd	*red_cmd(t_cmd *sub_cmd, char *file, char *e_file, int mode, int fd, t_token_type type);

//01_main.c
int		main(int ac, char **av, char **envp);
void	prompt_loop(t_minishell **msh);

//02_msh_init.c
void	ft_init_msh(t_minishell **msh, int ac, char **av, char **envp);
int		my_getpid(t_minishell *msh);
void	dup_envp(t_minishell *msh, t_list **l_envp, char **envp);

//03_tokenizer.c
void 		get_tokens(t_minishell **msh);
int			token_is_word(t_minishell **msh, int start);
int			token_is_pipe(t_minishell **msh, int start);
int			token_is_redir_r(t_minishell **msh, int start);
int			token_is_redir_l(t_minishell **msh, int start);
void		append_token(t_minishell *msh, t_token_lst *new_token, char *content, t_token_type type);
t_token_lst	*find_last_token(t_token_lst *token_list);

//get_cmd
//parse_cmd
//run_cmd

//10_close_msh.c
void	close_minishell(t_minishell	*msh, char *err_msg, int exit_code);
void	free_msh(t_minishell *msh);
void	handle_envp_failure(t_minishell *msh, char *str, t_list *list_node);

#endif