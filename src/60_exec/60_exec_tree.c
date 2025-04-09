/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   60_exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:24:34 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/09 16:53:48 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_tree(t_minishell **msh, t_tree_node *node)
{
	if (node->type == PIPE)
		exec_pipe(msh, node);
	else if (type_is_redir(&node->type))
		exec_redir(msh, node);
	else if (type_is_word(&node->type))
		exec_cmd(msh, node);
}
