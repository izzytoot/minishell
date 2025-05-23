/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   37_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:21:51 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/20 11:28:36 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_path(t_list *envp_list)
{
	while (envp_list)
	{
		if (!ft_strncmp(envp_list->content, "PATH=", 5))
			return (envp_list->content + 5);
		envp_list = envp_list->next;
	}
	return (NULL);
}

void	check_rep_cmd(t_msh **msh)
{
	t_tk_lst	*curr;
	bool		cmd_ch;

	curr = (*msh)->token_list;
	cmd_ch = false;
	while (curr && curr->next)
		curr = curr->next;
	while (curr)
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

bool	check_builtin(char *str)
{
	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "env") || (!ft_strcmp(str, "echo")
			|| !ft_strcmp(str, "export") || !ft_strcmp(str, "unset")
			|| !ft_strcmp(str, "exit")))
		return (true);
	return (false);
}

bool	check_shell_var(char *str)
{
	if (ft_strchr(str, '='))
	{
		if ((str[0] >= 'A' && str[0] <= 'Z')
			|| (str[0] >= 'a' && str[0] <= 'z'))
			return (true);
		else
			return (false);
	}
	return (false);
}

bool	tk_in_qts(t_tk_lst *tk)
{
	if (!tk)
		return (false);
	if (tk->quotes.in_dquotes || tk->quotes.in_squotes)
		return (true);
	return (false);
}
