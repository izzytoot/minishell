/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   33_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:21:51 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/20 19:25:20 by icunha-t         ###   ########.fr       */
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
/*
int	handle_quotes(t_minishell **msh,  char *word, char quote_char, int start)
{
	int			i;
	int			j;
	const char *line;
	
	i = start;
	j = 0;
	line = (*msh)->promt_line;
	ft_printf("word is: %s.\n", word);
	ft_printf("quote_char is: %c.\n", quote_char);
	ft_printf("start is: %d.\n", start);
	ft_printf("currently on %c and going to %c.\n", line[i], line[i + 1]);
	if (quote_char == '\'')
	{
		while(line[i] && line[i] != quote_char)
			word[j++] = line[i];
	}
	return (i);
}


		//ft_printf("%c", line[i]);
		//ft_printf("word is %s\n", word);

		*/