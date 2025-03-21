/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:17:48 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/21 15:16:00 by icunha-t         ###   ########.fr       */
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

bool	check_in_quotes(char c, bool *in_quotes, char quote_char)
{
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
