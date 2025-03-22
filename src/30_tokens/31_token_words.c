/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_token_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:07:53 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/22 19:59:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	token_is_word(t_minishell **msh, int start, bool *in_quotes)
{
	const char	*line;
	char		word[1000];
	int			i;
	int			j;
	//char		quote_char;
	t_token_lst	*new_token;
	
	line = (*msh)->promt_line;
	//quote_char = '\0';
	i = start;
	j = 0;
    while (line[i] && (!ft_strchr(OPERATOR, line[i]) || in_quotes) && (!ft_strchr(WHITESPACE, line[i]) || in_quotes))	
	{
		//if (ft_strchr(QUOTE, line[i]) && !in_quotes)
		//	check_quote(&in_quotes, &quote_char, line[i]);
		//else
			word[j++] = line[i];
		i++;
	}
	word[j] = '\0';
	new_token = calloc(1, sizeof(t_token_lst));
	append_token(*msh, new_token, word, WORD);
	return(i - 1);
}

