/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:33:00 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/17 13:39:44 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_tokens(t_minishell	**msh)
{
	int			i;
	const	char *line;
	
	i = 0;
	line = (*msh)->promt_line;
	while((*msh)->promt_line[i])
	{
		if (line[i] && !ft_strchr(TOKENS, line[i]) && !ft_strchr(WHITESPACE, line[i]))
			i = token_is_word(msh, i);
		else if (line[i] == '|')
			i = token_is_pipe(msh, i);
		else if (line[i] == '>')
			i = redir_r(msh, i);
		else if (line[i] == '<')
			i = redir_l(msh, i);
		else if (ft_strchr(WHITESPACE, line[i]))
			i++;
		else
			return ;
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
