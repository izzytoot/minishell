/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:33:00 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/14 20:51:29 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_tokens(t_msh **msh, int i)
{
	const char		*line;
	t_quote			quotes;
	
	init_qt_struct(&quotes);
	line = (*msh)->prompt_line;
	i = -1;
	empty_case(msh, (*msh)->prompt_line, 0, true);
	while(line[++i])
	{
		quotes.space_case = false;
		sort_out_quotes(&i, line, &quotes);
		if ((!quotes.in_squotes || !quotes.in_dquotes) && ft_strchr(QT, line [i]))
			i++;
		if (line[i] && line[i] != quotes.quote_char
			&& (extra_check(&(*msh), &i, line[i], &quotes)))
				;
		else if (line[i] == quotes.quote_char)
			i--;
		else
			break ;
	}
	if ((*msh)->debug_mode)  //DEBUG TO DELETE
	{	
		print_tokens(&(*msh));
		ft_printf("------------------------------\n");
	}
	sub_tokenize(&(*msh));
	if ((*msh)->debug_mode)  //DEBUG TO DELETE
	{	
		print_tokens(&(*msh));
		ft_printf("------------------------------\n");
	}
	parse_line(&(*msh));
	// ft_printf("------------------------------\n");
	// if ((*msh)->debug_mode)
	// 	print_tokens(&(*msh)); //DEBUG TO DELETE
	// ft_printf("------------------------------\n");
	return ;
}

void	init_qt_struct(t_quote *quotes)
{
	quotes->in_squotes = false;
	quotes->in_dquotes = false;
	quotes->quote_char = '\0';
}

bool	extra_check(t_msh **msh, int *i, char c, t_quote *quotes)
{	
	if (ft_strchr(WS, c) && !quotes->in_quotes)
		*i = tk_space(msh, *i);
	else if (!ft_strchr(OPERATOR, c) && !quotes->in_quotes)
		*i = tk_word(msh, *i);
	else if (quotes->in_quotes)
		*i = tk_word_qt(msh, *i, &quotes->in_quotes, &quotes->quote_char);
	else if (c == '|' && !quotes->in_quotes)
		*i = tk_pipe(msh, *i);
	else if (c == '>' && !quotes->in_quotes)
		*i = redir_r(msh, *i);
	else if (c == '<' && !quotes->in_quotes)
		*i = redir_l(msh, *i);
	else
		return (false);
	return (true);
}
