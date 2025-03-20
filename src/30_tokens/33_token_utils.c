/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   33_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:21:51 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/20 18:06:41 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	check_quote(char c, bool *quote_check, char *quote_char)
{
	bool	ret;

	ret = false;
	if (!*quote_check && (c == '\'' || c == '\"'))
	{
		ret = true;
		*quote_char = c;
	}
	else if (*quote_check && c == *quote_char)
		ret = false;
	return (ret);
}

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
			word[j++] = line[++i];
	}
	return (i);
}


		//ft_printf("%c", line[i]);
		//ft_printf("word is %s\n", word);