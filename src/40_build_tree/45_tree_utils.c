/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   45_tree_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:17:25 by isabel            #+#    #+#             */
/*   Updated: 2025/05/19 16:32:34 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tk_lst	*safe_next_tk(t_tk_lst *curr_tk)
{
	t_tk_lst	*next_tk;

	next_tk = curr_tk;
	if (next_tk->next && next_tk->next->type == W_SPACE)
		next_tk = next_tk->next->next;
	else
		next_tk = curr_tk->next;
	return (next_tk);
}

void	add_fname(t_tree_nd *new_redir, t_tk_lst *curr_tk)
{
	if (new_redir->type == REDIR_HD && curr_tk->prev
		&& curr_tk->prev->type == W_SPACE)
		new_redir->eof_ch = true;
	if (curr_tk->prev && curr_tk->prev->type == W_SPACE)
	{
		if (new_redir->type == REDIR_HD
			&& !(curr_tk->prev->prev->quotes.in_dquotes
				|| curr_tk->prev->prev->quotes.in_squotes))
			new_redir->exp_hd = true;
		new_redir->file = curr_tk->prev->prev->content;
		//new_redir->file = ft_strdup(curr_tk->prev->prev->content);	
	}
	else if (curr_tk->prev)
	{
		if (new_redir->type == REDIR_HD && !(curr_tk->prev->quotes.in_dquotes
				|| curr_tk->prev->quotes.in_squotes))
			new_redir->exp_hd = true;
		new_redir->file = curr_tk->prev->content;
		//new_redir->file = ft_strdup(curr_tk->prev->content);
	}
	else
		new_redir->file = ft_strdup("");
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

t_tree_nd	*add_left(t_tree_nd *redir_nd, t_tree_nd *cmd_nd, bool cmd_on_r)
{
	t_tree_nd	*leftmost;
	t_tree_nd	*final_redir;

	final_redir = redir_nd;
	leftmost = NULL;
	if (cmd_nd && !cmd_on_r)
	{
		leftmost = final_redir;
		while (leftmost->left)
			leftmost = leftmost->left;
		leftmost->left = cmd_nd;
	}
	else if (cmd_nd && cmd_on_r)
		final_redir->right = cmd_nd;
	return (final_redir);
}

t_list	*reverse_args(t_list **head)
{
	t_list	*prev;
	t_list	*curr;
	t_list	*next;

	prev = NULL;
	curr = *head;
	next = NULL;
	if (!head || !*head)
		return (NULL);
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
	return (*head);
}
