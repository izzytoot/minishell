/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   52_build_redir_nodes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:37:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/06 22:51:53 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree_nd	*build_redir_nd(t_msh **msh, t_tk_lst **token_list)
{
	t_tk_lst	*curr_tk;
	t_tree_nd	*redir_nd;
	t_tree_nd	*new_redir;
	t_tree_nd	*cmd_nd;

	curr_tk = *token_list;
	ft_init_var((void **)&redir_nd, (void **)&new_redir,
		(void **)&cmd_nd, NULL);
	while (curr_tk && (curr_tk->next || type_is_redir(&curr_tk->type)))
	{
		if (type_is_redir(&curr_tk->type))
			redir_nd = handle_redir(msh, redir_nd, &curr_tk);
		else
			curr_tk = curr_tk->next;
	}
	if (check_cmd(token_list))
		cmd_nd = build_cmd_nd(msh, token_list);
	if (redir_nd)
		return (add_left(redir_nd, cmd_nd));
	return (cmd_nd);
}

t_tree_nd	*handle_redir(t_msh **msh, t_tree_nd *redir_nd, t_tk_lst **curr_tk)
{
	t_tree_nd	*new_redir;

	if (!curr_tk || !*curr_tk)
		return (redir_nd);
	new_redir = new_tree_nd(NULL, &(*curr_tk)->type, &(*curr_tk)->content[0]);
	add_fname(msh, new_redir, (*curr_tk));
	new_redir->type = (*curr_tk)->type;
	if ((*curr_tk)->type == REDIR_IN || (*curr_tk)->type == REDIR_HD)
		new_redir->fd = STDIN_FILENO;
	else
		new_redir->fd = STDOUT_FILENO;
	redir_nd = attach_redir(redir_nd, new_redir);
	if ((!(*curr_tk)->next || next_is_redir(*curr_tk))
		&& check_prev((*curr_tk)))
		new_redir->cmd_r = true;
	*curr_tk = safe_next_tk(*curr_tk);
	return (redir_nd);
}

bool	check_cmd(t_tk_lst **token_list)
{
	t_tk_lst	*curr_tk;

	curr_tk = *token_list;
	while (curr_tk)
	{
		if (type_is_redir(&curr_tk->type))
		{
			if (curr_tk->next)
			{
				if (search_cmd(curr_tk, 1))
					return (true);
			}
			if (curr_tk->prev)
			{
				if (search_cmd(curr_tk, 0))
					return (true);
			}
			return (false);
		}
		if (curr_tk)
			curr_tk = safe_next_tk(curr_tk);
	}
	return (true);
}

bool	search_cmd(t_tk_lst *curr_tk, int way)
{
	if (way == 1)
	{
		while (curr_tk && (!type_is_redir(&curr_tk->type)
				|| !(curr_tk->type == FILE_NAME)))
		{
			if (type_is_word(&curr_tk->type))
				return (true);
			curr_tk = safe_next_tk(curr_tk);
		}
		if (curr_tk)
			curr_tk = safe_next_tk(curr_tk);
	}
	if (way == 0)
	{
		while (curr_tk && (!type_is_redir(&curr_tk->type)
				|| !(curr_tk->type == FILE_NAME)))
		{
			if (type_is_word(&curr_tk->type))
				return (true);
			curr_tk = safe_prev_tk(curr_tk);
		}
		if (curr_tk)
			curr_tk = safe_prev_tk(curr_tk);
	}
	return (false);
}
