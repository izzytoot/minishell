/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:17:48 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/14 15:54:27 by root             ###   ########.fr       */
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

char	*get_eof(const char *line, int hd_index)
{
	char	*eof;
	int		i;
	int		size;
	int		eof_s;
	
	hd_index++; // second <
	i = 0;
	size = 0;
	if (line[hd_index + 1] == ' ')
		hd_index++;
	hd_index++;
	eof_s = hd_index;
	while(!ft_strchr(WHITESPACE, line[++hd_index]))
		size++;
	eof = malloc(sizeof(char) * (size + 1));
	while(!ft_strchr(WHITESPACE, line[eof_s]))
	{
		eof[i] = line[eof_s];
		eof_s++;
		i++;
	}
	eof[i] = '\0';
	return(eof);
}
