/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   62_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:52:20 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/09 18:13:00 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_redir(t_minishell **msh, t_tree_node *node)
{
	int	file_fd;
	int	orig_fd;
	int	curr_pid;
	
	file_fd = create_file_fd(node->type, node->file);
	curr_pid = getpid();
	orig_fd = safe_dup(node->fd, curr_pid);
	safe_dup2(file_fd, node->fd, curr_pid);
	close(file_fd);
	if (node->left)
		exec_tree(msh, node->left);
	safe_dup2(orig_fd, node->fd, curr_pid);
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
	else
	{
		ft_dprintf(STDERR_FILENO, "msh: %s: %s\n", ERR_UNKRED, strerror(errno));
		return (STDERR_FILENO);
	}
	if (file_fd < 0)
	{
		ft_dprintf(STDERR_FILENO, "msh: %s: %s\n", file_name, strerror(errno));
		return (STDERR_FILENO);
	}
	return (file_fd);
}

