/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_build_redir_nodes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:37:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/19 16:35:16 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree_nd *build_redir_nd(t_msh **msh, t_tk_lst **token_list)
{
	t_tk_lst	*curr_tk;
	t_tree_nd	*redir_nd;
	t_tree_nd	*new_redir;
	t_tree_nd	*cmd_nd;
	bool		cmd_on_r;

	curr_tk = *token_list;
	cmd_on_r = false;
	ft_init_var((void **)&redir_nd, (void **)&new_redir,
		(void **)&cmd_nd, NULL);
	while (curr_tk && (curr_tk->next || type_is_redir(&curr_tk->type)))
	{
		if (type_is_redir(&curr_tk->type))
			redir_nd = handle_redir(redir_nd, &curr_tk, &cmd_on_r);
		else
			curr_tk = curr_tk->next;
	}
	if(check_cmd(token_list, cmd_on_r))
		cmd_nd = build_cmd_nd(msh, token_list);
	if (redir_nd)
		return (add_left(redir_nd, cmd_nd, cmd_on_r));
	return (cmd_nd);
}

bool	next_is_redir(t_tk_lst *curr_tk) // PASS TO ANOTHER FILE
{
	if (curr_tk->next->type == W_SPACE)
		curr_tk = curr_tk->next;
	if (curr_tk->next->type == FILE_NAME 
		|| ft_strchr(REDIR, curr_tk->next->content[0]))
		return (true);
	return (false);
}

t_tree_nd	*handle_redir(t_tree_nd *redir_nd, 
	t_tk_lst **curr_tk, bool *cmd_on_r)
{
	t_tree_nd	*new_redir;

	if (!curr_tk || !*curr_tk)
		return (redir_nd);
	new_redir = new_tree_nd(NULL, &(*curr_tk)->type, &(*curr_tk)->content[0]);
	add_fname(new_redir, (*curr_tk));
	new_redir->type = (*curr_tk)->type;
	if ((*curr_tk)->type == REDIR_IN || (*curr_tk)->type == REDIR_HD)
		new_redir->fd = STDIN_FILENO;
	else
		new_redir->fd = STDOUT_FILENO;
	redir_nd = attach_redir(redir_nd, new_redir);
	if ((!(*curr_tk)->next || next_is_redir(*curr_tk)) 
		&& check_prev((*curr_tk)))
		*cmd_on_r = true;
	*curr_tk = safe_next_tk(*curr_tk);
	return (redir_nd);
}

t_tree_nd	*attach_redir(t_tree_nd *redir_nd, t_tree_nd *new_redir)
{
	if (!redir_nd)
		return (new_redir);
	else
		redir_nd->left = attach_redir(redir_nd->left, new_redir);
	return (redir_nd);
}

bool	check_cmd(t_tk_lst **token_list, bool cmd_on_r)
{
	t_tk_lst	*curr_tk;

	curr_tk = *token_list;
	if (curr_tk->type == FILE_NAME && cmd_on_r)
		return (false);
	while (curr_tk)
	{
		if (type_is_redir(&curr_tk->type) && !cmd_on_r)
		{
			if (curr_tk->next)
			{
				if (search_cmd(curr_tk))
					return (true);
			}
			else
				return (false);
		}
		if (curr_tk)
			curr_tk = safe_next_tk(curr_tk);
	}
	return (true);
}

bool	search_cmd(t_tk_lst *curr_tk)
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
	return (false);
}
