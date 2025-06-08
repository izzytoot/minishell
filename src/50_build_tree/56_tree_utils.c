/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   56_tree_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:17:25 by isabel            #+#    #+#             */
/*   Updated: 2025/06/08 22:23:08 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tk_lst	*safe_next_tk(t_tk_lst *curr_tk)
{
	t_tk_lst	*next_tk;

	next_tk = curr_tk;
	if (next_tk->next && next_tk->next->next && next_tk->next->type == W_SPACE)
		next_tk = next_tk->next->next;
	else
		next_tk = curr_tk->next;
	return (next_tk);
}

t_tk_lst	*safe_prev_tk(t_tk_lst *curr_tk)
{
	t_tk_lst	*prev_tk;

	prev_tk = curr_tk;
	if (prev_tk->prev && prev_tk->prev->type == W_SPACE && prev_tk->prev->prev)
		prev_tk = prev_tk->prev->prev;
	else
		prev_tk = curr_tk->prev;
	return (prev_tk);
}

void	add_fname(t_msh **msh, t_tree_nd *new_redir, t_tk_lst *curr_tk)
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
		new_redir->file = ft_strdup(curr_tk->prev->prev->content);
		ch_ambg(msh, new_redir, new_redir->file, curr_tk->prev->prev);
	}
	else if (curr_tk->prev)
	{
		if (new_redir->type == REDIR_HD && !(curr_tk->prev->quotes.in_dquotes
				|| curr_tk->prev->quotes.in_squotes))
			new_redir->exp_hd = true;
		new_redir->file = ft_strdup(curr_tk->prev->content);
		ch_ambg(msh, new_redir, new_redir->file, curr_tk->prev);
	}
	else
		new_redir->file = ft_strdup("");
}

void	ch_ambg(t_msh **msh, t_tree_nd *new_redir, char *fname, t_tk_lst *tk)
{
	int		i;
	bool	qts;

	i = -1;
	qts = false;
	if (tk->quotes.in_dquotes || tk->quotes.in_squotes)
		qts = true;
	if (!fname)
		return ;
	if (!qts && fname[0])
	{
		while (fname[++i])
		{
			if (strchr(WS, fname[i]))
			{
				if ((*msh)->tmp_fname)
					(*msh)->tmp_fname = safe_free((*msh)->tmp_fname);
				(*msh)->tmp_fname = ft_strdup(fname);
				new_redir->ch_ambg = true;
				return ;
			}
		}
	}
	new_redir->ch_ambg = false;
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
