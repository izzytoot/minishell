/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   62_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:52:20 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/15 16:39:59 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_redir_before_cmd(t_minishell **msh, t_tree_node *node)
{
	t_redir_data	redir_data;
	t_tree_node 	*redir_nodes[32]; //adjust max redirects
	t_tree_node 	*current_node;
	int				i;
	
	current_node = node;
	redir_data.cmd_node = NULL;
	redir_data.orig_stdin = -1;
	redir_data.orig_stdout = -1;
	i = collect_redirs_and_cmd(&current_node, redir_nodes, &redir_data);
	while(--i >= 0)
		exec_redir(redir_nodes[i]); //exec redir from left to right
	if (redir_data.cmd_node)
		exec_tree(msh, redir_data.cmd_node); //exec cmd on the correct fd if cmd on the right
	if (redir_data.orig_stdin != -1)
		safe_dup2(redir_data.orig_stdin, 0, getpid()); //restore original fd - terminal
	if (redir_data.orig_stdout != -1)
		safe_dup2(redir_data.orig_stdout, 1, getpid()); //restore original fd - terminal
}

int	collect_redirs_and_cmd(t_tree_node **current_node, t_tree_node **redir_nodes, t_redir_data *redir_data)
{
	int	i;

	i = 0;
	while(*current_node && type_is_redir(&(*current_node)->type)) //collect redir from right to left
	{
		redir_nodes[i] = *current_node;
		if (((*current_node)->type == REDIR_IN || (*current_node)->type == REDIR_HD) && redir_data->orig_stdin == -1)
			redir_data->orig_stdin = safe_dup((*current_node)->fd, getpid());
		if (((*current_node)->type == REDIR_OUT || (*current_node)->type == REDIR_APP) && redir_data->orig_stdout == -1)
			redir_data->orig_stdout = safe_dup((*current_node)->fd, getpid());
		if ((*current_node)->right && type_is_cmd(&(*current_node)->right->type)) //keep cmd node if on right
			redir_data->cmd_node = (*current_node)->right;
		else if ((*current_node)->left && type_is_cmd(&(*current_node)->left->type)) //keep cmd node if on left
			redir_data->cmd_node = (*current_node)->left;
		*current_node = (*current_node)->left;
		i++;
	}
	return (i);
}

int	exec_redir(t_tree_node *node)
{
	int		file_fd;
	int		curr_pid;
	char	*file_name;
	
	if (node->type == REDIR_HD)
		file_name = ft_strdup("/tmp/.heredoc_tmp");
	else
		file_name = node->file;
	file_fd = create_file_fd(node->type, node->file);
	if (file_fd < 0)
		return (-1);
	curr_pid = getpid();
	if (node->type == REDIR_HD)
	{
		handle_hd(node, file_fd);
		close(file_fd);
		file_fd = open(node->file, O_RDONLY);
		if (file_fd < 0)
			return(-1);
	}
	safe_dup2(file_fd, node->fd, curr_pid);
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
