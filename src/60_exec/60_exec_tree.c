/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   60_exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:24:34 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/08 17:30:08 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_tree(t_minishell **msh, t_tree_node *node)
{
	if (node->type == PIPE)
		exec_pipe(msh, node);
	else if (type_is_redir(&node->type))
	{
		int	file_fd;
		
		file_fd = 0;
		if (node->type == REDIR_IN)
			file_fd = open(node->file, O_RDONLY);
		else if (node->type == REDIR_OUT)
			file_fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (node->type == REDIR_APP)
			file_fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file_fd < 0)
		{
			perror("open"); //check errors
			exit(1);
		}
		dup2(file_fd, node->fd);
		close(file_fd);
		exec_tree(msh, node->left);
	}
	else if (type_is_cmd(&node->type))
		exec_cmd(msh, node);
}
