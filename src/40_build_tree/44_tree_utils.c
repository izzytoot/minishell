/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   44_tree_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:36:26 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/21 13:47:11 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tk_lst *safe_next_tk(t_tk_lst *curr_tk)
{
	t_tk_lst *next_tk;
	
	next_tk = curr_tk;
	if (next_tk->next && next_tk->next->type == W_SPACE)
		next_tk = next_tk->next->next;
	else
		next_tk = curr_tk->next;
	return (next_tk);
}

bool	type_is_redir(t_tk_type *type)
{
	if (*type == REDIR_APP || *type == REDIR_HD || *type == REDIR_IN || *type == REDIR_OUT)
		return(true);
	else
		return (false);
}

bool	type_is_word(t_tk_type *type)
{
	if (*type == WORD || *type ==  ARG || *type == BT_CMD || *type == ENV_CMD)
		return(true);
	else
		return (false);
}

bool	type_is_cmd(t_tk_type *type)
{
	if (*type == BT_CMD || *type == ENV_CMD)
		return(true);
	else
		return (false);
}

bool	type_is_arg(t_tk_type *type)
{
	if (*type ==  ARG)
		return(true);
	else
		return (false);
}
