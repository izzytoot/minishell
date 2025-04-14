/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   62_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:52:20 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/14 19:33:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	exec_redir_before_cmd(t_minishell **msh, t_tree_node *node)
{
	t_tree_node *redir_nodes[32]; //adjust max redirects
	t_tree_node *current_node;
	t_tree_node	*cmd_node;
	int			orig_stdin = -1;
	int			orig_stdout = -1;
	int			i;
	int			j;
	
	current_node = node;
	cmd_node = NULL;
	i = 0;
	while(current_node && type_is_redir(&current_node->type)) //collect from right to left>
	{
		redir_nodes[i] = current_node;
		if ((current_node->type == REDIR_IN || current_node->type == REDIR_HD) && orig_stdin == -1)
			orig_stdin = safe_dup(0, getpid());
		if ((current_node->type == REDIR_OUT || current_node->type == REDIR_APP) && orig_stdout == -1)
			orig_stdout = safe_dup(1, getpid());
		if (current_node->right && type_is_cmd(&current_node->right->type)) //keep cmd node
			cmd_node = current_node->right;
		current_node = current_node->left;
		i++;
	}
	j = i - 1;
	while(j >= 0)
	{
		exec_redir(redir_nodes[j]); //exec redir from left to right
		j--;
	}
	if (current_node)
		exec_tree(msh, current_node); //exec cmd on the correct fd if cmd on the left
	else if (cmd_node)
		exec_tree(msh, cmd_node); //exec cmd on the correct fd if cmd on the right
	if (orig_stdin != -1)
		safe_dup2(orig_stdin, 0, getpid()); //restore original fd - terminal
	if (orig_stdout != -1)
		safe_dup2(orig_stdout, 1, getpid()); //restore original fd - terminal
}


/*
void	exec_redir_before_cmd(t_minishell **msh, t_tree_node *node)
{
	t_tree_node *current_node;
	t_tree_node	*cmd_node;
	int			orig_fd;
	int			fd_for_cmd;
	
	current_node = node;
	cmd_node = NULL;
	if (current_node->right && type_is_cmd(&current_node->right->type)) //keep cmd node
		cmd_node = current_node->right;
	orig_fd = safe_dup(node->fd, getpid());
	exec_redir(current_node); //exec first redir
	fd_for_cmd = safe_dup(node->fd, getpid()); //keep fd for cmd (only works for redir_in)
	current_node = current_node->left; 
	while (current_node && type_is_redir(&current_node->type)) //exec all other redir if there are any
	{
		exec_redir(current_node);
		current_node = current_node->left;
	}
	safe_dup2(fd_for_cmd, node->fd, getpid()); //recover fd for cmd
	if (current_node)
		exec_tree(msh, current_node); //exec cmd on the correct fd if cmd on the left
	else if (cmd_node)
		exec_tree(msh, cmd_node); //exec cmd on the correct fd if cmd on the right
	safe_dup2(orig_fd, node->fd, getpid()); //restore original fd - terminal
}
*/

int	exec_redir(t_tree_node *node)
{
	int	file_fd;
	int	curr_pid;
	
	file_fd = create_file_fd(node->type, node->file);
	if (file_fd < 0)
		return (-1);
	curr_pid = getpid();
	if (node->type == REDIR_HD)
	{
		handle_hd(node, file_fd); 
		node->fd = file_fd;
	}
	else
	{
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
}

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
		file_fd = open("/tmp/.heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0600); //hd temporary file
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
