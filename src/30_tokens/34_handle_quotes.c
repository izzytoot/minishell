/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   34_handle_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:53:10 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/09 00:28:02 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sort_out_quotes(t_msh **msh, const char *line, int *i, t_quote *quotes)
{
	quotes->sp_case = false;
	if (ft_strchr(QT, line[*i]) && ((*msh)->token_list
			&& (ft_strcmp("\'\'", (*msh)->token_list->content) == 0)))
		(*i)++;
	sort_quotes_util(msh, i, line, quotes);
	if ((!quotes->in_squotes || !quotes->in_dquotes)
		&& ft_strchr(QT, line[*i]))
		(*i)++;
}

void	sort_quotes_util(t_msh **msh, int *i, const char *line, t_quote *quotes)
{
	sort_empty_qt(msh, quotes);
	if ((!quotes->in_squotes && !quotes->in_dquotes)
		&& (ft_strchr(QT, line[*i])))
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

void	sort_empty_qt(t_msh **msh, t_quote *quotes)
{
	t_tk_lst	*last;

	last = (*msh)->token_list;
	if (!last)
		return ;
	if (quotes->in_quotes && last->content && (ft_strcmp("\'\'",
				last->content) == 0))
	{
		quotes->in_quotes = false;
		if (quotes->in_dquotes)
			quotes->in_dquotes = false;
		if (quotes->in_squotes)
			quotes->in_squotes = false;
	}
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
