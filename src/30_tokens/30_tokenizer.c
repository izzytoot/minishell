/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:33:00 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/26 00:44:22 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_tokens(t_minishell **msh, int i, char quote_char)
{
	const char *line;
	bool		in_quotes;

	line = (*msh)->promt_line;
	in_quotes = false;
	while(line[++i])
	{
		if (!in_quotes && ft_strchr(QUOTE, line[i]))
		{
			check_in_quotes(line[i], &in_quotes);
			if (in_quotes)
				quote_char = line[i];
		}
		else
		 check_in_quotes(line[i], &in_quotes);
		if (!in_quotes && ft_strchr(QUOTE, line[i]))
			i++;
		if (any_of_these(&(*msh), &i, line[i], in_quotes, quote_char))
		;
		else
			break ;
	}
	change_filename_type((*msh)->token_list);
	if ((*msh)->debug_mode)
			print_tokens(&(*msh)); //DEBUG TO DELETE
	parse_line(&(*msh));
	return ;
}

void	change_filename_type(t_token_lst *token_list)
{
	t_token_lst *current;

	current = token_list;
	while (current)
	{
		if (current->type == REDIR_APP || current->type == REDIR_IN || current->type == REDIR_OUT)
		{
			if (current->prev->type == W_SPACE && current->prev->prev->type == WORD)
				current->prev->prev->type = FILE_NAME;
			else if (current->prev->type == WORD)
				current->prev->type = FILE_NAME;
		}
		current = current->next;
	}
}

bool	any_of_these(t_minishell **msh, int *i, char c, bool in_quotes, char quote_char)
{
	bool	tmp_in_quotes;
	char	tmp_qt_char;
	
	tmp_in_quotes = in_quotes;
	tmp_qt_char = quote_char;
	if (ft_strchr(WHITESPACE, c) && !tmp_in_quotes)
		*i = token_is_space(msh, *i);
	else if (!ft_strchr(OPERATOR, c) && !tmp_in_quotes)
		*i = token_is_word(msh, *i);
	else if (!ft_strchr(OPERATOR, c) && tmp_in_quotes)	
		*i = token_is_word_in_quotes(msh, *i, &tmp_in_quotes, &tmp_qt_char);
	else if (c == '|' && !tmp_in_quotes)
		*i = token_is_pipe(msh, *i);
	else if (c == '>' && !tmp_in_quotes)
		*i = redir_r(msh, *i);
	else if (c == '<' && !tmp_in_quotes)
		*i = redir_l(msh, *i);
	else
		return (false);
	return (true);
}
