/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   62_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:52:20 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/08 19:27:46 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_redir(t_minishell **msh, t_tree_node *node)
{
	int	file_fd;

	if (node->type == REDIR_IN)
		file_fd = open(node->file, O_RDONLY);
	else if (node->type == REDIR_OUT)
		file_fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644); //user can read&write; others can only read
	else if (node->type == REDIR_APP)
		file_fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else // ?????
	{
		ft_putstr_fd(ERR_UNKRED, STDERR_FILENO);
		return ;
	}
	if (file_fd < 0)
	{
		perror("open");
		return ;
	}
	if (dup2(file_fd, node->fd) < 0)
	{
		perror("dup2");
		close(file_fd);
		return ;
	}
	close(file_fd);
	if (node->left)
		exec_tree(msh, node->left);
}
