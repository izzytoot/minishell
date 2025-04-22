/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   34_handle_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:53:10 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/22 18:15:11 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

// bool	check_in_quotes(char c, bool *in_squotes, bool *in_dquotes)
// {
// 	static char	quote_char;
// 	bool		res;

// 	res = false;
// 	if ((!(*in_squotes) && !(*in_dquotes)) && ft_strchr(QUOTE, c))
// 	{
// 		if (c == '"')
// 		{
// 			*in_squotes = true;
// 			res = true;
// 		}
// 		else if (c == 39)
// 			*in_dquotes = true;
// 		quote_char = c;
// 	}
// 	else if ((*in_squotes || *in_dquotes) && c == quote_char)
// 	{
// 		if (in_squotes)
// 			*in_squotes = false;
// 		else if (in_dquotes)
// 			*in_dquotes = false;
// 		quote_char = '\0';
// 	}
// 	return (in_squotes);
// }