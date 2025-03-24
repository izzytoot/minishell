/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   34_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:21:51 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/24 17:12:30 by icunha-t         ###   ########.fr       */
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
	new_token->next = msh->token_list;
	new_token->prev = NULL;
	if (msh->token_list)
		msh->token_list->prev = new_token;
	msh->token_list = new_token;
}
