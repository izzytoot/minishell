/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   60_exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:24:34 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/17 15:16:50 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_tree(t_minishell **msh, t_tree_node *node)
{
	if ((*msh)->hd_check)
	{
		exec_heredocs(node);
		(*msh)->hd_check = false;
	}	
	if (node->type == PIPE)
		exec_pipe(msh, node);
	else if (type_is_redir(&node->type))
		exec_redir_before_cmd(msh, node);
	else if (type_is_word(&node->type))
		exec_cmd(msh, node);
}

void	exec_heredocs(t_tree_node *node)
{
	int	file_fd;
//	int	orig_stdin;
	
	if (!node)
		return ;
	if (node->type == REDIR_HD)
	{	
	//	orig_stdin = safe_dup(node->fd, getpid());
		node->tmp_file = ft_strdup("/home/icunha-t/Commoncore/minishell/.heredoc_tmp"); //change dir later
		file_fd = create_file_fd(node->type, node->tmp_file);
	//	safe_dup2(file_fd, node->fd, getpid());
		handle_hd(node, file_fd);
	//	safe_dup2(orig_stdin, STDIN_FILENO, getpid());
		close(file_fd);
	}
	if (node->left)
		exec_heredocs(node->left);
	if(node->right)
		exec_heredocs(node->right);
}
