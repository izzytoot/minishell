/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   41_build_pipe_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:38:23 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/02 16:42:47 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree_node *build_pipe_node(t_token_lst **token_list)
{
	t_token_lst *curr_token;
	t_tree_node	*pipe_node;
	t_token_lst *left_tokens;
	t_token_lst *prev_token;
	 
	curr_token = *token_list;
	pipe_node = NULL;
	prev_token = NULL;
	while(curr_token)
	{
		if (curr_token->type == PIPE)
		{
			pipe_node = new_tree_node(&curr_token->type, &curr_token->content[0]);
			curr_token = curr_token->next;
			left_tokens = curr_token;
			prev_token->next = NULL; // cut right list
			left_tokens->prev = NULL;// cut left list
			pipe_node->right = build_redir_node(token_list);
			pipe_node->left = build_pipe_node (&left_tokens);
			return (pipe_node);
		}
		prev_token = curr_token;
		curr_token = curr_token->next;
	}
	return(build_redir_node(token_list));
}
