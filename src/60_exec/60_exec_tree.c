/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   60_exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:24:34 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/01 15:48:56 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_tree(t_msh **msh, t_tree_nd *node)
{
	expand_tree(msh, node);
	expand_files(msh, node);
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
