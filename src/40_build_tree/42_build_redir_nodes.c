/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_build_redir_nodes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:37:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/04 16:16:35 by icunha-t         ###   ########.fr       */
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
	while(curr_token && (curr_token->next || type_is_redir(&curr_token->type)))
	{
		if(type_is_redir(&curr_token->type))
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
		return (add_leftmost(redir_node, cmd_node));
	return (cmd_node);
}

void handle_redir(t_tree_node *redir_node, t_token_lst *curr_token)
{
	if (!curr_token || !curr_token->prev)
		return;
	if (curr_token->prev->type == W_SPACE)
		redir_node->file = ft_strdup(curr_token->prev->prev->content);
	else
		redir_node->file = ft_strdup(curr_token->prev->content);
	redir_node->type = curr_token->type;
	if (curr_token->type == REDIR_IN)
		redir_node->fd = STDIN_FILENO;
	else
		redir_node->fd = STDOUT_FILENO;
}

t_tree_node *attach_redir(t_tree_node *redir_node, t_tree_node *new_redir)
{
    if (!redir_node) 
        return (new_redir);
	else
		redir_node->left = attach_redir(redir_node->left, new_redir);
    return (redir_node);
}

bool check_cmd(t_token_lst **token_list)
{
	t_token_lst *curr_token;
	
	curr_token = *token_list;
	while(curr_token)
	{
		if(type_is_redir(&curr_token->type))
		{
			if (curr_token->next)
			{
				while(!type_is_redir(&curr_token->type))
				{
					if(type_is_word(&curr_token->type))
						break;
					curr_token = curr_token->next;
				}
				if (!type_is_word(&curr_token->type))
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
	leftmost = NULL;
	if (cmd_node)
	{
		leftmost = final_redir;
		while(leftmost->left)
			leftmost = leftmost->left;
		leftmost->left = cmd_node;
	}
	return(final_redir);
}

