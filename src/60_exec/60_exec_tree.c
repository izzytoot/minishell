/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   60_exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:24:34 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/02 15:52:56 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_tree(t_msh **msh, t_tree_nd *node)
{
	int	status;

	status = 0;
	expand_tree(msh, node);
	expand_files(msh, node);
	if ((*msh)->hd_check)
	{
		exec_heredocs(msh, node);
		(*msh)->hd_check = false;
	}	
	if (node->type == PIPE)
		status = exec_pipe(msh, node);
	else if (type_is_redir(&node->type))
		status = exec_redir_before_cmd(msh, node);
	else if (type_is_word(&node->type))
		status = exec_cmd(msh, node);
	return (exit_value(msh, status, 1, 0));
}
