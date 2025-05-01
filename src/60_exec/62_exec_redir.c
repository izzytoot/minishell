/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   62_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:52:20 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/21 13:37:16 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_redir_before_cmd(t_msh **msh, t_tree_nd *node)
{
	t_redir_data	redir_data;
	t_tree_nd 	*redir_nodes[32]; //adjust max redirects
	t_tree_nd 	*curr_node;
	int				i;
	
	curr_node = node;
	redir_data.cmd_nd = NULL;
	redir_data.orig_stdin = -1;
	redir_data.orig_stdout = -1;
	i = collect_redirs_and_cmd(&curr_node, redir_nodes, &redir_data);
	while(--i >= 0)
		exec_redir(redir_nodes[i]); //exec redir from left to right
	if (redir_data.cmd_nd)
		exec_tree(msh, redir_data.cmd_nd); //exec cmd on the correct fd if cmd on the right
	if (redir_data.orig_stdin != -1)
		safe_dup2(redir_data.orig_stdin, 0, getpid()); //restore original fd - terminal
	if (redir_data.orig_stdout != -1)
		safe_dup2(redir_data.orig_stdout, 1, getpid()); //restore original fd - terminal
}

int	collect_redirs_and_cmd(t_tree_nd **curr_node, t_tree_nd **redir_nodes, t_redir_data *redir_data)
{
	int	i;

	i = 0;
	while(*curr_node && type_is_redir(&(*curr_node)->type)) //collect redir from right to left
	{
		redir_nodes[i] = *curr_node;
		if (((*curr_node)->type == REDIR_IN || (*curr_node)->type == REDIR_HD) && redir_data->orig_stdin == -1)
			redir_data->orig_stdin = safe_dup((*curr_node)->fd, getpid());
		if (((*curr_node)->type == REDIR_OUT || (*curr_node)->type == REDIR_APP) && redir_data->orig_stdout == -1)
			redir_data->orig_stdout = safe_dup((*curr_node)->fd, getpid());
		if ((*curr_node)->right && type_is_cmd(&(*curr_node)->right->type)) //keep cmd node if on right
			redir_data->cmd_nd = (*curr_node)->right;
		else if ((*curr_node)->left && type_is_cmd(&(*curr_node)->left->type)) //keep cmd node if on left
			redir_data->cmd_nd = (*curr_node)->left;
		*curr_node = (*curr_node)->left;
		i++;
	}
	return (i);
}

int	exec_redir(t_tree_nd *node)
{
	int		file_fd;
	int		curr_pid;
	
	file_fd = -1;
	if (node->type != REDIR_HD)
		file_fd = create_file_fd(node->type, node->file);
	if (node->type == REDIR_HD)
		file_fd = open(node->tmp_file, O_RDONLY);
	if (file_fd < 0)
		return (-1);
	curr_pid = getpid();
	if (node->type == REDIR_HD)
	{
	 	file_fd = open(node->tmp_file, O_RDONLY);
	 	safe_dup2(file_fd, STDIN_FILENO, curr_pid);
	 	close(file_fd);
	}
	else
		safe_dup2(file_fd, node->fd, curr_pid);
	return (0);
}

int create_file_fd(t_tk_type type, char *file_name)
{
	int	file_fd;

	if (type == REDIR_IN)
		file_fd = open(file_name, O_RDONLY);
	else if (type == REDIR_OUT)
		file_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644); //644 user can read&write; others can only read
	else if (type == REDIR_APP)
		file_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == REDIR_HD)
		file_fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0600); //hd temporary file
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
