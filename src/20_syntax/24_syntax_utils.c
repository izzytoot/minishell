/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:17:48 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/11 20:44:20 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../inc/minishell.h"

bool	look_for_pipe(const char *line, int i)
{
	i++;
	if (!line[i])
		return (false);
	while (line[i] && (ft_strchr(WHITESPACE, line[i]) || ft_strchr(QUOTE, line[i])))
		i++;
	if(line[i] == '|')
	{
		ft_putstr_fd(ERR_SYN_PIPE, STDERR_FILENO);
		return (true);
	}	
	return (false);
}

bool	check_in_quotes(char c, bool *in_quotes)
{
	static char quote_char;
	
 	if (!(*in_quotes) && ft_strchr(QUOTE, c))
	{
		*in_quotes = true;
		quote_char = c;
	}
	else if (*in_quotes && c == quote_char)
	{
		*in_quotes = false;
		quote_char = '\0';
	}
	return (in_quotes);
}

int check_if_hd(const char *line)
{
	int		i;
	bool	in_quotes;

	i = -1;
	in_quotes = false;
	while(line[++i])
	{
		check_in_quotes(line[i], &in_quotes);
		if (line[i] && !in_quotes && (line[i] == '<' && line[i + 1] == '<'))
			return (i);
	}
	return (-1);
}
