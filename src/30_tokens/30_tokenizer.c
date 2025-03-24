/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:33:00 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/24 00:11:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/*
void	get_tokens(t_minishell **msh, int i, char quote_char)
{
	const char *line;
	bool	in_quotes;
	
	line = (*msh)->promt_line;
	in_quotes = false;
	while(line[++i])
	{
		while (line[i] && ft_strchr(WHITESPACE, line[i]))
        	i++;
		if (!in_quotes && ft_strchr(QUOTE, line[i]))
		{
			check_in_quotes(line[i], &in_quotes);
			if (in_quotes)
				quote_char = line[i];
		}
		else
		 check_in_quotes(line[i], &in_quotes);
		if (line[i] && !ft_strchr(OPERATOR, line[i]) && !in_quotes)
			i = token_is_word(msh, i);
		else if (line[i] && !ft_strchr(OPERATOR, line[i]) && in_quotes)	
			i = token_is_word_in_quotes(msh, i, &in_quotes, &quote_char);
		else if (line[i] == '|' && !in_quotes)
			i = token_is_pipe(msh, i);
		else if (line[i] == '>' && !in_quotes)
			i = redir_r(msh, i);
		else if (line[i] == '<' && !in_quotes)
			i = redir_l(msh, i);
		else if (ft_strchr(WHITESPACE, line[i]))
			i++;
		else
			break ;
	}
	return ;
}
*/
void	get_tokens(t_minishell **msh, int i, char quote_char)
{
	const char *line;
	bool	in_quotes;
	
	line = (*msh)->promt_line;
	in_quotes = false;
	while(line[++i])
	{
		while (line[i] && ft_strchr(WHITESPACE, line[i]))
        	i++;
		if (!in_quotes && ft_strchr(QUOTE, line[i]))
		{
			check_in_quotes(line[i], &in_quotes);
			if (in_quotes)
				quote_char = line[i];
		}
		else
		 check_in_quotes(line[i], &in_quotes);
		if (any_of_these(&(*msh), &i, line[i], in_quotes, quote_char))
		;
		else
			break ;
	}
	return ;
}

bool	any_of_these(t_minishell **msh, int *i, char c, bool in_quotes, char quote_char)
{
	bool	tmp_in_quotes;
	char	tmp_qt_char;
	
	tmp_in_quotes = in_quotes;
	tmp_qt_char = quote_char;
	if (!ft_strchr(OPERATOR, c) && !tmp_in_quotes)
		*i = token_is_word(msh, *i);
	else if (!ft_strchr(OPERATOR, c) && tmp_in_quotes)	
		*i = token_is_word_in_quotes(msh, *i, &tmp_in_quotes, &tmp_qt_char);
	else if (c == '|' && !tmp_in_quotes)
		*i = token_is_pipe(msh, *i);
	else if (c == '>' && !tmp_in_quotes)
		*i = redir_r(msh, *i);
	else if (c == '<' && !tmp_in_quotes)
		*i = redir_l(msh, *i);
	else if (ft_strchr(WHITESPACE, c))
		*i = *i + 1;
	else
		return (false);
	return (true);
}
