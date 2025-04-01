/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   40_tokens_to_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:07:28 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/01 18:48:29 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parse_line(t_minishell **msh)
{
	t_tree_node *tree_root;
	
	if (!(*msh)->token_list)
		return ;
	(*msh)->tree_root = build_pipe_node(&(*msh)->token_list);
	tree_root = (*msh)->tree_root;
	if ((*msh)->debug_mode)
		print_tree(tree_root);
}

t_tree_node *build_pipe_node(t_token_lst **token_list)
{
	t_token_lst *curr_token;
	t_tree_node	*pipe_node;
	t_token_lst *left_tokens;
	t_token_lst *prev_token;
	 
	curr_token = *token_list;
	pipe_node = NULL;
	prev_token = NULL;
	while(curr_token)
	{
		if (curr_token->type == PIPE)
		{
			pipe_node = new_tree_node(&curr_token->type, &curr_token->content[0]);
			curr_token = curr_token->next;
			left_tokens = curr_token;
			prev_token->next = NULL; // cut right list
			left_tokens->prev = NULL;// cut left list
			pipe_node->right = build_redir_node(token_list);
			pipe_node->left = build_pipe_node (&left_tokens);
			return (pipe_node);
		}
		prev_token = curr_token;
		curr_token = curr_token->next;
	}
	return(build_redir_node(token_list));
}

t_tree_node *build_redir_node(t_token_lst **token_list)
{
	t_token_lst	*curr_token;
	t_tree_node *redir_node;
	t_tree_node *new_redir;
	t_tree_node *cmd_node;
	t_tree_node *leftmost;
//	bool		cmd_check;
	
	curr_token = *token_list;
//	cmd_check = true;
	if (!curr_token)
		return NULL;
	redir_node = NULL;
	while(curr_token)
	{
		if (!curr_token->next && (curr_token->type != REDIR_IN))
			break;
		if(tk_is_redir(&curr_token->type))
		{
			new_redir = new_tree_node(&curr_token->type, &curr_token->content[0]);
			handle_redir(new_redir, curr_token);
			redir_node = attach_redir(redir_node, new_redir);
			if (curr_token->next && curr_token->next->type == W_SPACE)
				curr_token = curr_token->next->next;
			else
				curr_token = curr_token->next;
		}
		else
			curr_token = curr_token->next;
	}
	cmd_node = build_cmd_node(token_list);
	if (redir_node)
	{
		leftmost = redir_node;
		while(leftmost->left)
			leftmost = leftmost->left;
		leftmost->left = cmd_node;
		return (redir_node);
	}
	return (cmd_node);
}
/*
if (curr_token->next && curr_token->next->type == W_SPACE)
			{
				if ((curr_token = curr_token->next->next) == NULL)
					cmd_check = false;
				curr_token = curr_token->next->next;
			}
			else
			{
				if ((curr_token = curr_token->next) == NULL)
					cmd_check = false;
				curr_token = curr_token->next;
			}
*/

t_tree_node *build_cmd_node(t_token_lst **token_list)
{
	t_token_lst	*curr_token;
	t_list 		*args;
	t_tree_node *cmd_node;

	curr_token = *token_list;
	if (!curr_token)
        return NULL;
	args = NULL;
	cmd_node = new_tree_node(&curr_token->type, NULL);
	while(curr_token)
	{
		if (tk_is_cmd(&curr_token->type))
		{
			ft_lstadd_back(&args, ft_lstnew(ft_strdup(curr_token->content)));
			cmd_node->type = curr_token->type;
			curr_token = curr_token->next;
		}
		else
			curr_token = curr_token->next;
	}
	cmd_node->args = ft_list_to_array(args);
	cmd_node->content = ft_unsplit(cmd_node->args);
	if (curr_token)
		*token_list = curr_token;
	return(cmd_node);
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
