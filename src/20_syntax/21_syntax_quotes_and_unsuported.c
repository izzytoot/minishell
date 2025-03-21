/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_syntax_quotes_and_unsuported.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:05:45 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/21 18:35:46 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../inc/minishell.h"

bool	empty_quotes(const char *line)
{
	int	i;
	
	i = -1;
	while(line[++i])
	{
		if (ft_strchr(QUOTE, line[i]) && line[i + 1] == line[i])
		{
			ft_putstr_fd(ERR_SYN_EMPT, STDERR_FILENO);
			return (true);
		}
	}
	return (false);
}

bool unclosed_quotes(const char *line)
{
	bool in_quotes;
	char last_quote_c;
	int	i;
	bool prev_in_quotes;
	
	in_quotes = false;
	last_quote_c = '\0';
	i = 0;
    while (line[i])
    {
        prev_in_quotes = in_quotes;
        check_in_quotes(line[i], &in_quotes);
        if (!prev_in_quotes && in_quotes)
            last_quote_c = line[i];
        i++;
    }
    if (in_quotes)
    {
        if (last_quote_c == '\'')
            ft_putstr_fd(ERR_SYN_SQT, STDERR_FILENO);
        else if (last_quote_c == '\"')
            ft_putstr_fd(ERR_SYN_DQT, STDERR_FILENO);
        return (true);
    }
    return (false);
}

bool	unsupported_operators(const char *line)
{
	int		i;
	bool	in_quotes;

	i = -1;
	in_quotes = false;
	while(line[++i])
	{
		check_in_quotes(line[i], &in_quotes);
		if (!in_quotes && (line[i] == '|' && line[i + 1] == '|'))
		{
			ft_putstr_fd(ERR_SYN_UNS_OP, STDERR_FILENO);
			return (true);
		}
		if (!in_quotes && (line[i] == '&' && line[i + 1] == '&'))
		{
			ft_putstr_fd(ERR_SYN_UNS_OP, STDERR_FILENO);
			return (true);
		}	
	}
	return (false);
}
