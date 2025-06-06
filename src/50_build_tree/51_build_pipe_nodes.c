/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   51_build_pipe_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:38:23 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/06 14:36:17 by ddo-carm         ###   ########.fr       */
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
			pipe_nd = new_tree_nd(NULL, &curr_token->type, "|");
			bd_pp_nd_util(&next_token, &curr_token, &left_tokens, &prev_token);
			pipe_nd->right = build_redir_nd(msh, token_list);
			free_tokens(*token_list, 2);
			*token_list = NULL;
			pipe_nd->left = build_pipe_nd(msh, &left_tokens);
			if (left_tokens != NULL)
				free_tokens(left_tokens, 2);
			return (pipe_nd);
		}
		move_fwd(&prev_token, &curr_token);
	}
	return (build_redir_nd(msh, token_list));
}

void	bd_pp_nd_util(t_tk_lst	**n_tk, t_tk_lst **c_tk,
		t_tk_lst **l_tk, t_tk_lst **p_tk)
{
	*n_tk = (*c_tk)->next;
	free_tokens(*c_tk, 1);
	*c_tk = *n_tk;
	*l_tk = *c_tk;
	(*p_tk)->next = NULL;
	(*l_tk)->prev = NULL;
}

void	move_fwd(t_tk_lst **prev_tk, t_tk_lst **curr_tk)
{
	*prev_tk = *curr_tk;
	*curr_tk = (*curr_tk)->next;
}
