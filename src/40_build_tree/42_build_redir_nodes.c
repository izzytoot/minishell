/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_build_redir_nodes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:37:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/10 17:24:22 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree_node *build_redir_node(t_token_lst **token_list)
{
	t_token_lst	*curr_token;
	t_tree_node *redir_node;
	t_tree_node *new_redir;
	t_tree_node *cmd_node;
	bool		cmd_excep;
	
	curr_token = *token_list;
	cmd_excep = false;
	ft_init_var((void **)&redir_node, (void **)&new_redir, (void **)&cmd_node, NULL);
	while(curr_token && (curr_token->next || type_is_redir(&curr_token->type)))
	{
		if(type_is_redir(&curr_token->type))
			redir_node = handle_redir(redir_node, &curr_token, &cmd_excep);
		else
			curr_token = curr_token->next;
	}
	if(check_cmd(token_list, cmd_excep))
		cmd_node = build_cmd_node(token_list);
	if (redir_node)
		return (add_leftmost(redir_node, cmd_node, cmd_excep));
	return (cmd_node);
}

t_tree_node *handle_redir(t_tree_node *redir_node, t_token_lst **curr_token, bool *cmd_excep)
{
	t_tree_node *new_redir;
	
	if (!curr_token || !*curr_token)
		return (redir_node);

	new_redir = new_tree_node(&(*curr_token)->type, &(*curr_token)->content[0]);
	if ((*curr_token)->prev && (*curr_token)->prev->type == W_SPACE)
		new_redir->file = ft_strdup((*curr_token)->prev->prev->content);
	else if ((*curr_token)->prev)
		new_redir->file = ft_strdup((*curr_token)->prev->content);
	else
		new_redir->file = NULL;
	new_redir->type = (*curr_token)->type;
	if ((*curr_token)->type == REDIR_IN)
		new_redir->fd = STDIN_FILENO;
	else
		new_redir->fd = STDOUT_FILENO;
	redir_node = attach_redir(redir_node, new_redir);
	if (!(*curr_token)->next)
		*cmd_excep = true;
	*curr_token = safe_next_token(*curr_token);
	return(redir_node);	
}

t_tree_node *attach_redir(t_tree_node *redir_node, t_tree_node *new_redir)
{
    if (!redir_node) 
        return (new_redir);
	else
		redir_node->left = attach_redir(redir_node->left, new_redir);
    return (redir_node);
}

bool check_cmd(t_token_lst **token_list, bool cmd_excep)
{
	t_token_lst *curr_token;
	
	curr_token = *token_list;
	if(curr_token->type == FILE_NAME && cmd_excep)
		return (false);
	while(curr_token)
	{
		if(type_is_redir(&curr_token->type) && !cmd_excep)
		{
			if (curr_token->next)
			{
				while(!type_is_redir(&curr_token->type) || !(curr_token->type == FILE_NAME))
				{
					if(type_is_word(&curr_token->type))
						return (true);
					curr_token = safe_next_token(curr_token);
				}
				curr_token = safe_next_token(curr_token);
				// if (!type_is_word(&curr_token->type))
				// 	return (false); acho que nao é preciso - tirar
			}
			else
				return (false);
		}
		curr_token = safe_next_token(curr_token);;
	}
	return (true);
}

t_tree_node	*add_leftmost(t_tree_node *redir_node, t_tree_node *cmd_node, bool cmd_excep)
{
	t_tree_node *leftmost;
	t_tree_node *final_redir;

	final_redir = redir_node;
	leftmost = NULL;
	if (cmd_node && !cmd_excep)
	{
		leftmost = final_redir;
		while(leftmost->left)
			leftmost = leftmost->left;
		leftmost->left = cmd_node;
	}
	else if (cmd_node && cmd_excep)
		final_redir->right = cmd_node;
	return(final_redir);
}

