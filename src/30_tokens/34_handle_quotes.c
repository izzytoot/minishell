/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   34_handle_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:53:10 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/18 16:03:40 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sort_out_quotes(int *i, const char *line, t_quote *quotes)
{
	if ((!quotes->in_squotes && !quotes->in_dquotes) && ft_strchr(QT, line[*i]))
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

	if (!(*in_squotes) && ft_strchr(QT, c))
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

	if (!(*in_dquotes) && ft_strchr(QT, c))
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
