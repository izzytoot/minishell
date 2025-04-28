/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   34_handle_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:53:10 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/23 12:49:59 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sort_out_quotes(int *i, const char *line, t_quote *quotes)
{
	if ((!quotes->in_squotes && !quotes->in_dquotes) && ft_strchr(QUOTE, line[*i]))
		{
			check_squote(&quotes->in_squotes, line[*i]);
			check_dquote(&quotes->in_dquotes, line[*i]);
			if (quotes->in_squotes || quotes->in_dquotes)
				quotes->quote_char = line[*i];
		}
		else
		{
			check_squote(&quotes->in_squotes, line[*i]);
			check_dquote(&quotes->in_dquotes, line[*i]);
		}
		if (quotes->in_squotes || quotes->in_dquotes)
			quotes->in_quotes = true;
		else
			quotes->in_quotes = false;
}

void	check_squote(bool *in_squotes, char c)
{
	static char	quote_char;

	if (!(*in_squotes) && ft_strchr(QUOTE, c))
	{
		if (c == 39)
			*in_squotes = true;
		quote_char = c;
	}
	else if (*in_squotes && c == quote_char)
	{
		*in_squotes = false;
		quote_char = '\0';
	}
}

void	check_dquote(bool *in_dquotes, char c)
{
	static char	quote_char;

	if (!(*in_dquotes) && ft_strchr(QUOTE, c))
	{
		if (c == '"')
			*in_dquotes = true;
		quote_char = c;
	}
	else if (*in_dquotes && c == quote_char)
	{
		*in_dquotes = false;
		quote_char = '\0';
	}
}
