/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:33:00 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/23 18:23:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

