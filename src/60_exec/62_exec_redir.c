/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   62_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:52:20 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/11 17:10:31 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_redir_before_cmd(t_minishell **msh, t_tree_node *node)
{
	t_tree_node *current_node;
	t_tree_node	*cmd_node;
	int			orig_fd;
	int			fd_for_cmd;
	
	current_node = node;
	cmd_node = NULL;
	if (current_node->right && type_is_cmd(&current_node->right->type))
		cmd_node = current_node->right;
	orig_fd = safe_dup(node->fd, getpid());
	exec_redir(current_node); //exec first redir
	fd_for_cmd = safe_dup(node->fd, getpid()); //keep fd for cmd
	while (current_node && type_is_redir(&current_node->type)) //exec all other redir if there are any
	{
		exec_redir(current_node);
		current_node = current_node->left;
	}
	safe_dup2(fd_for_cmd, node->fd, getpid()); //recover fd for cmd
	if (current_node)
		exec_tree(msh, current_node); //exec cmd on the correct fd
	else if (cmd_node)
		exec_tree(msh, cmd_node);
	safe_dup2(orig_fd, node->fd, getpid()); //restore original fd - terminal
}

int	exec_redir(t_tree_node *node)
{
	int	file_fd;
	int	curr_pid;
	
	file_fd = create_file_fd(node->type, node->file);
	if (node->type == REDIR_HD)
		handle_hd(node, file_fd);
	else
	{
		curr_pid = getpid();
		safe_dup2(file_fd, node->fd, curr_pid);
		close(file_fd);
	}
	return (0);
}

void		handle_hd(t_tree_node *node, int hd_fd)
{
	t_tree_node *current_node;
	char 		*eof;
	char		*new_line;
	
	current_node = node;
	eof = ft_strdup(current_node->file);
	// close fd 0 read ??
	while(1)
	{
		new_line = readline("> ");
		if (!new_line)
			break;
		if (ft_strcmp(new_line, eof) == 0)
		{
			free(new_line);
			break ;
		}
		ft_putstr_fd(new_line, hd_fd);
		free(new_line);
		new_line = NULL;
	}
	node->fd = hd_fd;
}

// void	handle_here_doc(t_pipex *pipex)
// {
// 	char		*line;
// 	const char	*limiter;

// 	limiter = pipex->av[2];
// 	close(pipex->pipe_fd[0]);
// 	while (1)
// 	{
// 		ft_printf("pipex here_doc> ");
// 		line = get_next_line(STDIN_FILENO);
// 		if (!line)
// 			break ;
// 		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
// 			&& line[ft_strlen(limiter)] == '\n')
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(pipex->pipe_fd[1], line, ft_strlen(line));
// 		free(line);
// 		line = NULL;
// 	}
// 	close(pipex->pipe_fd[1]);
// }

int create_file_fd(t_token_type type, char *file_name)
{
	int	file_fd;
	
	if (type == REDIR_IN)
		file_fd = open(file_name, O_RDONLY);
	else if (type == REDIR_OUT)
		file_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644); //644 user can read&write; others can only read
	else if (type == REDIR_APP)
		file_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == REDIR_HD)
	{
		file_name = "/tmp/.heredoc_tmp";
		file_fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0600); //hd temporary file
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "msh: %s: %s\n", ERR_UNKRED, strerror(errno));
		return (-1);
	}
	if (file_fd < 0)
	{
		ft_dprintf(STDERR_FILENO, "msh: %s: %s\n", file_name, strerror(errno));
		return (-1);
	}
	return (file_fd);
}
