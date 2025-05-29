/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   41_build_pipe_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:38:23 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/29 15:24:04 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree_nd	*build_pipe_nd(t_msh **msh, t_tk_lst **token_list)
{
	t_tk_lst	*curr_token;
	t_tree_nd	*pipe_nd;
	t_tk_lst	*left_tokens;
	t_tk_lst	*prev_token;
	t_tk_lst	*next_token;
	
	curr_token = *token_list;
	ft_init_var((void **)&pipe_nd, (void **)&prev_token, NULL, NULL);
	while (curr_token)
	{
		if (curr_token->type == PIPE)
		{
			pipe_nd = new_tree_nd(NULL, &curr_token->type,
					&curr_token->content[0]);
			next_token = curr_token->next;
			free_tokens(curr_token, 1);
			curr_token = next_token;
			left_tokens = curr_token;
			prev_token->next = NULL;
			left_tokens->prev = NULL;
			pipe_nd->right = build_redir_nd(msh, token_list);
			free_tokens(*token_list, 2);
			pipe_nd->left = build_pipe_nd(msh, &left_tokens);
			free_tokens(left_tokens, 2);
			return (pipe_nd);
		}
		prev_token = curr_token;
		curr_token = curr_token->next;
	}
	return (build_redir_nd(msh, token_list));
}
