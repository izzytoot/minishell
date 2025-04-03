/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   44_tree_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:36:26 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/03 15:43:07 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree_node *attach_redir(t_tree_node *redir_node, t_tree_node *new_redir)
{
    if (!redir_node) 
        return (new_redir);
	else
		redir_node->left = attach_redir(redir_node->left, new_redir);
    return (redir_node);
}

bool	tk_is_redir(t_token_type *type)
{
	if (*type == REDIR_APP || *type == REDIR_HD || *type == REDIR_IN || *type == REDIR_OUT)
		return(true);
	else
		return (false);
}

bool	tk_is_word(t_token_type *type)
{
	if (*type == WORD || *type ==  ARG || *type == BT_CMD || *type == ENV_CMD)
		return(true);
	else
		return (false);
}

bool	tk_is_cmd(t_token_type *type)
{
	if (*type == BT_CMD || *type == ENV_CMD)
		return(true);
	else
		return (false);
}

bool	tk_is_arg(t_token_type *type)
{
	if (*type ==  ARG)
		return(true);
	else
		return (false);
}