/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   40_parse_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:07:28 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/26 00:46:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parse_line(t_minishell **msh)
{
	t_tree_node *tree_root;
	
	if (!(*msh)->token_list)
		return ;
	(*msh)->tree_root = build_tree(&(*msh)->token_list);
	tree_root = (*msh)->tree_root;
	if ((*msh)->debug_mode)
		print_tree(tree_root);
}

t_tree_node *build_tree(t_token_lst **token_list)
{
	t_token_lst *current_token;
	t_tree_node	*pipe_node;
	t_token_lst *right_tokens;
	t_token_lst *prev_token;
	 
	current_token = *token_list;
	pipe_node = NULL;
	prev_token = NULL;
	while(current_token)
	{
		if (current_token->type == PIPE)
		{
			pipe_node = new_tree_node(&current_token->type);
			current_token = current_token->next;
			right_tokens = current_token;
			prev_token->next = NULL; // cut left list
			pipe_node->right = build_tree (&right_tokens);
			pipe_node->left = build_tree(token_list);
			return (pipe_node);
		}
		prev_token = current_token;
		current_token = current_token->next;
	}
	return(build_cmd_or_redir_node(token_list));
}

t_tree_node *build_cmd_or_redir_node(t_token_lst **token_list)
{
	t_token_lst	*current_token;
	t_list 		*args;
	t_tree_node *node;
	
	current_token = *token_list;
	if (!current_token)
        return NULL;
	args = NULL;
	node = new_tree_node(&current_token->type);
	while(current_token)
	{
		if (current_token->type == REDIR_OUT || current_token->type == REDIR_IN || current_token->type == REDIR_APP)
		{
			handle_redir(node, current_token);
			if (current_token->next->type == W_SPACE)
				current_token = current_token->next->next; //to skip filename token
			else
				current_token = current_token->next->next;
		}
		else if (current_token->type == WORD)
		{
			ft_lstadd_back(&args, ft_lstnew(ft_strdup(current_token->content)));
			current_token = current_token->next;
		}
		else
			current_token = current_token->next;
	}
	node->args = conv_list_to_array(args);
	if (current_token)
		*token_list = current_token;
	return(node);
}

void handle_redir(t_tree_node *redir_node, t_token_lst *current_token)
{
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
