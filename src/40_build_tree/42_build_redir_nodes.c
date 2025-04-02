/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_build_redir_nodes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:37:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/02 18:48:33 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree_node *build_redir_node(t_token_lst **token_list)
{
	t_token_lst	*curr_token;
	t_tree_node *redir_node;
	t_tree_node *new_redir;
	t_tree_node *cmd_node;
	
	curr_token = *token_list;
	ft_init_var((void **)&redir_node, (void **)&new_redir, (void **)&cmd_node, NULL);
	while(curr_token)
	{
		if (!curr_token->next && !tk_is_redir(&curr_token->type))
			break;
		if(tk_is_redir(&curr_token->type))
		{
			new_redir = new_tree_node(&curr_token->type, &curr_token->content[0]);
			handle_redir(new_redir, curr_token);
			redir_node = attach_redir(redir_node, new_redir);
			curr_token = safe_next_token(curr_token);
		}
		else
			curr_token = curr_token->next;
	}
	if(check_cmd(token_list))
		cmd_node = build_cmd_node(token_list);
	if (redir_node)
	{
		redir_node = add_leftmost(redir_node, cmd_node);
		return (redir_node);
	}
	return (cmd_node);
}

void handle_redir(t_tree_node *redir_node, t_token_lst *current_token)
{
	if (!current_token || !current_token->prev)
		return;
	if (current_token->prev->type == W_SPACE)
		redir_node->file = ft_strdup(current_token->prev->prev->content);
	else
		redir_node->file = ft_strdup(current_token->prev->content);
	redir_node->type = current_token->type;
	if (current_token->type == REDIR_IN)
		redir_node->fd = STDIN_FILENO;
	else
		redir_node->fd = STDOUT_FILENO;
}

bool check_cmd(t_token_lst **token_list)
{
	t_token_lst *curr_token;
	
	curr_token = *token_list;
	while(curr_token)
	{
		if(tk_is_redir(&curr_token->type))
		{
			if (curr_token->next)
			{
				while(!tk_is_cmd(&curr_token->type))
				{
					if(tk_is_cmd(&curr_token->type))
						break;
					curr_token = curr_token->next;
				}
				/*
				if (curr_token->next->type == W_SPACE)
					curr_token = curr_token->next->next;
				else
					curr_token = curr_token->next;
				*/
				if (!tk_is_cmd(&curr_token->type))
					return (false);
			}
			else
				return (false);
		}
		curr_token = curr_token->next;
	}
	return (true);
}

t_tree_node	*add_leftmost(t_tree_node *redir_node, t_tree_node *cmd_node)
{
	t_tree_node *leftmost;
	t_tree_node *final_redir;

	final_redir = redir_node;
	if (cmd_node)
	{
		leftmost = final_redir;
		while(leftmost->left)
			leftmost = leftmost->left;
		leftmost->left = cmd_node;
	}
	return(final_redir);
}


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
