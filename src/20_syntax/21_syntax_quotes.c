/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_syntax_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:05:45 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/21 14:20:11 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	unclosed_quotes(const char *line)
{
	bool	in_quotes;
	char	last_quote_c;
	int		i;
	bool	prev_in_quotes;

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
