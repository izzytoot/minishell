/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   40_tokens_to_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:07:28 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/11 17:36:00 by icunha-t         ###   ########.fr       */
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
	if ((*msh)->debug_mode) //FOR DEBUGGING
		print_tree(tree_root);
}

t_tree_node *new_tree_node(t_token_type *type, char *content)
{
	t_tree_node *new_node;

	new_node = ft_calloc(1, sizeof(t_tree_node));
	if (!new_node)
		return (NULL);
	if (content)
		new_node->op_content = ft_strdup(content);
	new_node->cmd_content = NULL;
	if (type)
		new_node->type = *type;
	else
		new_node->type = -1;
	new_node->args = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->straight = NULL;
	new_node->cmd = NULL;
	new_node->fd = -1;
	return (new_node);
}
