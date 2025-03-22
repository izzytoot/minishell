/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:33:00 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/22 19:49:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_tokens(t_minishell	**msh)
{
	int			i;
	const char *line;
	bool		in_quotes;
	
	i = -1;
	line = (*msh)->promt_line;
	in_quotes = false;
	while(line[++i])
	{
		while (line[i] && ft_strchr(WHITESPACE, line[i]))
        	i++;
		check_in_quotes(line[i], &in_quotes);
		if (line[i] && !ft_strchr(OPERATOR, line[i]))
			i = token_is_word(msh, i, &in_quotes);
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

