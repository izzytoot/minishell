/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   35_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:21:51 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/23 11:59:05 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	app_tk(t_msh *msh, t_tk_lst *new_tk, char *content, t_tk_type type)
{
	new_tk->type = type;
	new_tk->content = ft_strdup(content);
	if (!new_tk->content)
	{
        free(new_tk);
        return ;
    }
	new_tk->next = msh->token_list;
	new_tk->prev = NULL;
	if (msh->token_list)
		msh->token_list->prev = new_tk;
	msh->token_list = new_tk;
}

char *get_path(t_list *envp_list)
{
	while(envp_list)
	{
		if (!ft_strncmp(envp_list->content, "PATH=", 5))
			return(envp_list->content + 5);
		envp_list = envp_list->next;
	}
	return (NULL);
}

void check_rep_cmd(t_msh **msh)
{
	t_tk_lst 	*curr;
	bool		cmd_ch;
	
	curr = (*msh)->token_list;
	cmd_ch = false;
	while (curr && curr->next)
		curr = curr->next;
	while(curr)
	{
		if (type_is_cmd(&curr->type))
		{
			if (cmd_ch)
				curr->type = ARG;
			else
				cmd_ch = true;
		}
		curr = curr->prev;
		if (curr && curr->type == PIPE)
			cmd_ch = false;
	}
}

bool			check_builtin(char *str)
{
	if (!ft_strcmp(str, "pwd")|| !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "env") || (!ft_strcmp(str, "echo")
		|| !ft_strcmp(str, "export") || !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "exit")))
		return (true);
	return (false);
}