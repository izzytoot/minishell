/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   40_parse_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:07:28 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/24 18:08:42 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parse_line(t_minishell **msh)
{	
	if (!(*msh)->token_list)
		return ;
	build_tree((*msh)->token_list);
}

t_token_lst *build_tree(t_token_lst **token_list)
{
	t_token_lst *current_token;
	t_tree_node	*tree_node;
	
	current_token = token_list;
	tree_node = NULL;
	while(current_token)
	{
		if (current_token->type == PIPE)
		{
			tree_node = add_node_to_tree(PIPE);
			tree_node->right = build_tree (current_token->next);
			current_token->next = NULL;
			tree_node->left = build_tree(token_list);
			return (tree_node);
		}
		current_token = current_token->next;
	}
	return(build_cmd_node(token_list));
}

t_tree_node *build_cmd_node(t_token_lst **token_list)
{
	
}

/*

AI VERSION
t_tree_node *build_command_node(t_token_lst **tokens)
{
    t_tree_node *cmd_node = new_node(CMD, NULL, NULL);
    t_list      *args = NULL;
    t_token_lst *curr = *tokens;

    while (curr && curr->type != PIPE)
    {
        if (curr->type == REDIR_OUT || curr->type == REDIR_IN)
        {
            handle_redirection(cmd_node, curr);
            curr = curr->next->next; // Skip filename token
        }
        else if (curr->type == WORD)
        {
            ft_lstadd_back(&args, ft_lstnew(ft_strdup(curr->content)));
            curr = curr->next;
        }
        else
            curr = curr->next; // Skip whitespace
    }
    
    // Convert list to array
    cmd_node->args = list_to_array(args);
    *tokens = curr; // Update token pointer
    return cmd_node;
}
void handle_redirection(t_tree_node *node, t_token_lst *tok)
{
    node->file = ft_strdup(tok->next->content); // Next token is filename
    node->type = tok->type;
    node->fd = (tok->type == REDIR_OUT) ? STDOUT_FILENO : STDIN_FILENO;
}
*/

t_tree_node *add_node_to_tree(t_token_type *type)
{
	
}
/*
AI version

t_tree_node *new_node(t_token_type type, t_tree_node *l, t_tree_node *r)
{
    t_tree_node *n = ft_calloc(1, sizeof(t_tree_node));
    n->type = type;
    n->left = l;
    n->right = r;
    return n;
}
*/