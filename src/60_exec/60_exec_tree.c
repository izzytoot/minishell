/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   60_exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:24:34 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/16 19:10:36 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_tree(t_minishell **msh, t_tree_node *node)
{
	collect_heredocs(node);
	if (node->type == PIPE)
		exec_pipe(msh, node);
	else if (type_is_redir(&node->type))
		exec_redir_before_cmd(msh, node);
	else if (type_is_word(&node->type))
		exec_cmd(msh, node);
}

void	collect_heredocs(t_tree_node *node)
{
	int	file_fd;
	
	if (!node)
		return ;
	if (node->type == REDIR_HD)
	{	
		node->tmp_file = ft_strdup("/tmp/.heredoc_tmp");
		file_fd = create_file_fd(node->type, node->tmp_file);
		handle_hd(node, file_fd);
		close(file_fd);
	}
	if (node->left)
		collect_heredocs(node->left);
	if(node->right)
		collect_heredocs(node->right);
}
