/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   40_tokens_to_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:07:28 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/21 13:43:30 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parse_line(t_msh **msh)
{
	t_tree_nd	*tree_root;
	
	if (!(*msh)->token_list)
		return ;
	(*msh)->tree_root = build_pipe_nd(&(*msh)->token_list);
	tree_root = (*msh)->tree_root;
	if ((*msh)->debug_mode) //FOR DEBUGGING
		print_tree(tree_root);
}

t_tree_nd *new_tree_nd(t_tk_type *type, char *content)
{
	t_tree_nd *new_nd;

	new_nd = ft_calloc(1, sizeof(t_tree_nd));
	if (!new_nd)
		return (NULL);
	if (content)
		new_nd->op_content = ft_strdup(content);
	new_nd->cmd_content = NULL;
	if (type)
		new_nd->type = *type;
	else
		new_nd->type = -1;
	new_nd->args = NULL;
	new_nd->left = NULL;
	new_nd->right = NULL;
	new_nd->cmd = NULL;
	new_nd->fd = -1;
	new_nd->cmd_type = -1;
	new_nd->eof_ch = false;
	new_nd->tmp_file = NULL;
	return (new_nd);
}
