/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   54_build_cmd_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:38:38 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/08 22:23:19 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree_nd	*build_cmd_nd(t_msh **msh, t_tk_lst **token_list)
{
	t_tk_lst	*curr_token;
	t_list		*args;
	t_tree_nd	*cmd_nd;

	curr_token = *token_list;
	if (!curr_token)
		return (NULL);
	while (curr_token && curr_token->type == W_SPACE)
		curr_token = curr_token->next;
	args = NULL;
	cmd_nd = new_tree_nd(curr_token, &curr_token->type, NULL);
	while (curr_token)
	{
		if (type_is_word(&curr_token->type))
			handle_cmd(msh, cmd_nd, &curr_token, &args);
		else
			curr_token = curr_token->next;
	}
	args = reverse_args(&args);
	cmd_nd->nb_arg = ft_lstsize(args);
	if (args)
		ft_list_to_array(&cmd_nd->args, &args);
	ft_lstclear(&args, free);
	cmd_nd->cmd_content = join_cmd_and_args(cmd_nd->cmd, cmd_nd->args);
	return (cmd_nd);
}

void	handle_cmd(t_msh **msh, t_tree_nd *cmd_nd, t_tk_lst **curr_tk,
	t_list **args)
{
	while (*curr_tk)
	{
		if (type_is_cmd(&(*curr_tk)->type) && !(*curr_tk)->quotes.sp_case
			&& (*curr_tk)->prev)
			(*curr_tk)->type = (*curr_tk)->type;
		if (type_is_arg(&(*curr_tk)->type))
			ft_lstadd_back(&(*args),
				ft_lstnew(ft_strdup((*curr_tk)->content)));
		if (type_is_cmd(&(*curr_tk)->type))
		{
			cmd_nd->cmd = ft_strdup((*curr_tk)->content);
			cmd_nd->cmd_type = (*curr_tk)->type;
		}
		if (type_is_word(&(*curr_tk)->type))
		{
			if ((*curr_tk)->type == ARG && (*curr_tk)->content[0] == '$'
				&& (*curr_tk)->content[1] && !ch_env_cont((*msh)->envp_list,
					(*msh)->vars_list, (*curr_tk)->content + 1))
				;
			else
				cmd_nd->type = (*curr_tk)->type;
		}
		*curr_tk = (*curr_tk)->next;
	}
}

char	**join_cmd_and_args(char *cmd, char **args)
{
	int		arg_count;
	char	**full_cmd;
	int		i;

	arg_count = 0;
	full_cmd = NULL;
	if (!cmd)
		return (ft_array_dup(args));
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

char	*ch_env_cont(t_list *envp_list, t_list *vars_list, char *key_word)
{
	int		key_len;

	key_len = ft_strlen(key_word);
	while (envp_list)
	{
		if (!ft_strncmp(envp_list->content, key_word, key_len)
			&& ((char *)envp_list->content)[key_len] == '=')
			return (&((char *)envp_list->content)[key_len + 1]);
		envp_list = envp_list->next;
	}
	while (vars_list)
	{
		if (!ft_strncmp(vars_list->content, key_word, key_len)
			&& ((char *)vars_list->content)[key_len] == '=')
			return (&((char *)vars_list->content)[key_len + 1]);
		vars_list = vars_list->next;
	}
	return (NULL);
}
