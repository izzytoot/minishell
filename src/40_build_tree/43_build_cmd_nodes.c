/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   43_build_cmd_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:38:38 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/03 19:11:04 by icunha-t         ###   ########.fr       */
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
		if (tk_is_word(&curr_token->type))
			handle_cmd(cmd_node, &curr_token, &args);
		else
			curr_token = curr_token->next;
	}
	cmd_node->args = ft_list_to_array(args);
	if (cmd_node->args)
		cmd_node->content = ft_strjoin_w_space(cmd_node->cmd, ft_unsplit(cmd_node->args));
	else
		cmd_node->content = cmd_node->cmd;
	if (curr_token)
		*token_list = curr_token;
	return(cmd_node);
}

void	handle_cmd(t_tree_node *cmd_node, t_token_lst **curr_token, t_list **args)
{
	while(*curr_token)
	{
		if (tk_is_arg(&(*curr_token)->type))
			ft_lstadd_back(&(*args), ft_lstnew(ft_strdup((*curr_token)->content)));
		if (tk_is_cmd(&(*curr_token)->type))
		{
			cmd_node->cmd = (*curr_token)->content;
			cmd_node->cmd_type = (*curr_token)->type;
		}
		cmd_node->type = (*curr_token)->type;
		*curr_token = (*curr_token)->next;
	}
}