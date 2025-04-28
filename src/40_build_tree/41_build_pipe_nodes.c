/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   41_build_pipe_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:38:23 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/23 14:28:54 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree_nd *build_pipe_nd(t_tk_lst **token_list)
{
	t_tk_lst *curr_token;
	t_tree_nd	*pipe_nd;
	t_tk_lst *left_tokens;
	t_tk_lst *prev_token;
	 
	curr_token = *token_list;
	ft_init_var((void **)&pipe_nd, (void **)&prev_token, NULL, NULL);
	while(curr_token)
	{
		if (curr_token->type == PIPE)
		{
			pipe_nd = new_tree_nd(NULL, &curr_token->type, &curr_token->content[0]);
			curr_token = curr_token->next;
			left_tokens = curr_token;
			prev_token->next = NULL; // cut right list
			left_tokens->prev = NULL;// cut left list
			pipe_nd->right = build_redir_nd(token_list);
			pipe_nd->left = build_pipe_nd(&left_tokens);
			return (pipe_nd);
		}
		prev_token = curr_token;
		curr_token = curr_token->next;
	}
	return(build_redir_nd(token_list));
}
