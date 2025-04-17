/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   34_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:21:51 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/17 16:39:26 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_quote(bool *in_quotes, char *quote_char, char c)
{
	if (!(*in_quotes))
    {
		*in_quotes = true;
		*quote_char = c;
	}
	else if (*in_quotes && c == *quote_char)
	{
		*in_quotes = false;
		*quote_char = '\0';
	}
}

void	append_token(t_minishell *msh, t_token_lst *new_token, char *content, t_token_type type)
{
	new_token->type = type;
	new_token->content = ft_strdup(content);
	if (!new_token->content)
	{
        free(new_token);
        return ;
    }
	new_token->next = msh->token_list;
	new_token->prev = NULL;
	if (msh->token_list)
		msh->token_list->prev = new_token;
	msh->token_list = new_token;
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

void check_double_cmd(t_minishell **msh)
{
	t_token_lst *current;
	bool		cmd_ch;
	
	current = (*msh)->token_list;
	cmd_ch = false;
	while (current && current->next)
		current = current->next;
	while(current)
	{
		if (type_is_cmd(&current->type))
		{
			if (cmd_ch)
				current->type = ARG;
			else
				cmd_ch = true;
		}
		current = current->prev;
	}
}
