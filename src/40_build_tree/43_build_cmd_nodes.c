/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   43_build_cmd_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:38:38 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/10 14:42:04 by icunha-t         ###   ########.fr       */
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
		if (type_is_word(&curr_token->type))
			handle_cmd(cmd_node, &curr_token, &args);
		else
			curr_token = curr_token->next;
	}
	cmd_node->args = ft_list_to_array(args);
	cmd_node->cmd_content =  join_cmd_and_args(cmd_node->cmd, cmd_node->args);
	return(cmd_node);
}

void	handle_cmd(t_tree_node *cmd_node, t_token_lst **curr_token, t_list **args)
{
	while(*curr_token)
	{
		if (type_is_arg(&(*curr_token)->type))
			ft_lstadd_back(&(*args), ft_lstnew(ft_strdup((*curr_token)->content)));
		if (type_is_cmd(&(*curr_token)->type))
		{
			cmd_node->cmd = (*curr_token)->content;
			cmd_node->cmd_type = (*curr_token)->type;
		}
		if (type_is_word(&(*curr_token)->type))
			cmd_node->type = (*curr_token)->type;
		*curr_token = (*curr_token)->next;
	}
}

char **join_cmd_and_args(char *cmd, char **args)
{
	int		arg_count;
	char	**full_cmd;
	int		i;

	arg_count = 0;
	full_cmd = NULL;
	if (!cmd)
	 	return (args);
	while (args && args[arg_count])
		arg_count++;
	full_cmd = malloc(sizeof(char *) * (arg_count + 2));
	if (!full_cmd)
		return (NULL);
	full_cmd[0] = ft_strdup(cmd);
	i = 0;
	while (i < arg_count)
	{
		full_cmd[i + 1] = ft_strdup(args[i]);
		i++;
	}
	full_cmd[i + 1] = NULL;
	return (full_cmd);
}
