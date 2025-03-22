/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   33_token_in_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:21:51 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/22 19:17:07 by root             ###   ########.fr       */
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
	t_token_lst *last;
	
	new_token->type = type;
	new_token->content = ft_strdup(content);
	new_token->next = NULL;
	new_token->prev = NULL;
	if (!msh->token_list)
		msh->token_list = new_token;
	else
	{
		last = find_last_token(msh->token_list);
		last->next = new_token;
		new_token->prev = last;
	}
}

t_token_lst	*find_last_token(t_token_lst *token_list)
{
	t_token_lst	*current;
	
	current = token_list;
	while(current && current->next)
		current = current->next;
	return(current);
}