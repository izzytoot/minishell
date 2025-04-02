/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   43_build_cmd_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:38:38 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/02 16:40:45 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
