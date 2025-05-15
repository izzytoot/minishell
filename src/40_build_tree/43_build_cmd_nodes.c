/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   43_build_cmd_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:38:38 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/15 16:44:39 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree_nd *build_cmd_nd(t_tk_lst **token_list)
{
	t_tk_lst	*curr_token;
	t_list 		*args;
	t_tree_nd 	*cmd_nd;

	curr_token = *token_list;
	if (!curr_token)
        return NULL;
	while(curr_token && curr_token->type == W_SPACE)
		curr_token = curr_token->next;
	args = NULL;
	cmd_nd = new_tree_nd(curr_token, &curr_token->type, NULL);
	while(curr_token)
	{
		if (type_is_word(&curr_token->type))
			handle_cmd(cmd_nd, &curr_token, &args);
		else
			curr_token = curr_token->next;
	}
	args = reverse_args(&args);
	cmd_nd->nb_arg = ft_lstsize(args);
	cmd_nd->args = ft_list_to_array(args);
	cmd_nd->cmd_content =  join_cmd_and_args(cmd_nd->cmd, cmd_nd->args);
	return(cmd_nd);
}

void	handle_cmd(t_tree_nd *cmd_nd, t_tk_lst **curr_tk, t_list **args)
{
	while(*curr_tk)
	{
		if (type_is_cmd(&(*curr_tk)->type) && !(*curr_tk)->quotes.space_case && (*curr_tk)->prev)
			(*curr_tk)->type = (*curr_tk)->type;
		if (type_is_arg(&(*curr_tk)->type))
			ft_lstadd_back(&(*args), ft_lstnew((*curr_tk)->content));
			//ft_lstadd_back(&(*args), ft_lstnew(ft_strdup((*curr_tk)->content)));
		if (type_is_cmd(&(*curr_tk)->type))
		{
				cmd_nd->cmd = (*curr_tk)->content;
				cmd_nd->cmd_type = (*curr_tk)->type;
		}
		if (type_is_word(&(*curr_tk)->type))
			cmd_nd->type = (*curr_tk)->type;
		*curr_tk = (*curr_tk)->next;
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
	full_cmd = ft_calloc((arg_count + 2), sizeof(char *));
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
