/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_syntax_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:05:45 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/22 19:14:15 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../inc/minishell.h"

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
