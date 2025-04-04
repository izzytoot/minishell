/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   44_tree_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:36:26 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/04 13:09:37 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token_lst *safe_next_token(t_token_lst *curr_token)
{
	t_token_lst *next_token;
	
	next_token = curr_token;
	if (next_token->next && next_token->next->type == W_SPACE)
		next_token = next_token->next->next;
	else
		next_token = curr_token->next;
	return (next_token);
}

bool	type_is_redir(t_token_type *type)
{
	if (*type == REDIR_APP || *type == REDIR_HD || *type == REDIR_IN || *type == REDIR_OUT)
		return(true);
	else
		return (false);
}

bool	type_is_word(t_token_type *type)
{
	if (*type == WORD || *type ==  ARG || *type == BT_CMD || *type == ENV_CMD)
		return(true);
	else
		return (false);
}

bool	type_is_cmd(t_token_type *type)
{
	if (*type == BT_CMD || *type == ENV_CMD)
		return(true);
	else
		return (false);
}

bool	type_is_arg(t_token_type *type)
{
	if (*type ==  ARG)
		return(true);
	else
		return (false);
}
