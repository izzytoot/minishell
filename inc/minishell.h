/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:50:18 by root              #+#    #+#             */
/*   Updated: 2025/03/10 17:40:08 by icunha-t         ###   ########.fr       */
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
//etc.
# define MAXCMD 10 //ver se posso
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

typedef enum	e_node_type
{
	PIPE,
	SEQ,
	BACK,
	EXEC,
	REDIR,
}	t_node_type;

typedef struct s_cmd
{
	t_node_type	type;
}	t_cmd;

typedef struct s_pipe_cmd // |
{
	t_node_type	type;
	t_cmd 		*left;
	t_cmd		*right;
}	t_pipe_cmd;

typedef struct s_seq // ; ver se este entra
{
	t_node_type	type;
	t_cmd		*left;
	t_cmd		*right;
}	t_seq;

typedef struct s_back //& ver se este entra
{
	t_node_type	type;
	t_cmd		*b_cmd;
}	t_back;

typedef struct	s_exec
{
	t_node_type	type;
	char		**s_av;
	char		**e_av;
}	t_exec;

typedef struct	s_red
{
	t_node_type	type;
	t_cmd		*r_cmd;
	char		*file;
	char		*e_file;
	int			fd_mode;
	int			fd;
	
}	t_red;
/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */
//00_main.c
int	main(void);


//get_cmd
//parse_cmd
//run_cmd

#endif