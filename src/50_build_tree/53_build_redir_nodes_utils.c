/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   43_build_redir_nodes_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:50:27 by isabel            #+#    #+#             */
/*   Updated: 2025/05/23 19:37:44 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	next_is_redir(t_tk_lst *curr_tk)
{
	if (!curr_tk->next)
		return (false);
	if (curr_tk->next->type == W_SPACE)
		curr_tk = curr_tk->next;
	if (curr_tk->next && (curr_tk->next->type == FILE_NAME
			|| ft_strchr(REDIR, curr_tk->next->content[0])))
		return (true);
	return (false);
}

bool	check_prev(t_tk_lst *curr_tk)
{
	t_tk_lst	*curr_tmp;

	if (!curr_tk->prev)
		return (false);
	curr_tmp = curr_tk->prev;
	while (curr_tmp && (curr_tmp->type == W_SPACE
			|| curr_tmp->type == FILE_NAME))
		curr_tmp = curr_tmp->prev;
	if (curr_tmp && type_is_word(&curr_tmp->type))
		return (true);
	return (false);
}

t_tree_nd	*add_left(t_tree_nd *redir_nd, t_tree_nd *cmd_nd)
{
	t_tree_nd	*leftmost;
	t_tree_nd	*final_redir;

	final_redir = redir_nd;
	leftmost = NULL;
	if (cmd_nd && !final_redir->cmd_r)
	{
		leftmost = final_redir;
		while (leftmost->left)
			leftmost = leftmost->left;
		leftmost->left = cmd_nd;
	}
	else if (cmd_nd && final_redir->cmd_r)
		final_redir->right = cmd_nd;
	return (final_redir);
}

t_tree_nd	*attach_redir(t_tree_nd *redir_nd, t_tree_nd *new_redir)
{
	if (!redir_nd)
		return (new_redir);
	else
		redir_nd->left = attach_redir(redir_nd->left, new_redir);
	return (redir_nd);
}
