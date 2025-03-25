/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   40_parse_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:07:28 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/25 19:24:10 by icunha-t         ###   ########.fr       */
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
		print_tree(tree_root, 0);
}

t_tree_node *build_tree(t_token_lst **token_list)
{
	t_token_lst *current_token;
	t_tree_node	*pipe_node;
	 t_token_lst *prev_token = NULL; //correct
	 
	current_token = *token_list;
	pipe_node = NULL;
	while(current_token)
	{
		if (current_token->type == PIPE)
		{
			pipe_node = new_tree_node(&current_token->type, NULL, NULL);
			current_token = current_token->next;
			t_token_lst *right_tokens = current_token; //correct
			if(prev_token)
				 prev_token->next = NULL;
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
	t_tree_node *cmd_node;
	
	current_token = *token_list;
	if (!current_token)
        return NULL;
	args = NULL;
	cmd_node = new_tree_node(&current_token->type, NULL, NULL);
	while(current_token && current_token->type != PIPE)
	{
		if (current_token->type == REDIR_OUT || current_token->type == REDIR_IN)
		{
			handle_redir(cmd_node, current_token);
			if (current_token->next->type == W_SPACE)
				current_token = current_token->next->next->next; //to skip filename token
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
	cmd_node->args = conv_list_to_array(args);
	if (current_token)
		*token_list = current_token;
	return(cmd_node);
}

void handle_redir(t_tree_node *redir_node, t_token_lst *current_token)
{
	redir_node->file = ft_strdup(current_token->next->content);
	redir_node->type = current_token->type;
	if (current_token->type == REDIR_OUT)
		redir_node->fd = STDOUT_FILENO;
	else
		redir_node->fd = STDIN_FILENO;
}
