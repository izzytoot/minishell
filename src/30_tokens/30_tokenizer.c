/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:33:00 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/08 11:55:42 by isabel           ###   ########.fr       */
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
	while(line[++i])
	{
		quotes.space_case = false;
		sort_out_quotes(&i, line, &quotes);
		if ((!quotes.in_squotes || !quotes.in_dquotes) && ft_strchr(QT, line [i]))
			i++;
		if (!ft_strchr(QT, line[i]) && (extra_check(&(*msh), &i, line[i], &quotes)))
				;
		else if (ft_strchr(QT, line[i]))
			i--;
		else
			break ;
	}
	sub_tokenize(&(*msh));
	empty_case(msh);
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

void	empty_case(t_msh **msh)
{
	t_tk_lst	*empty_tk;
	
	if (!(*msh)->token_list)
	{
		empty_tk = ft_calloc(1, sizeof(t_tk_lst));
		app_tk((*msh), empty_tk, "''", ARG);	
	}
	return ;
}

bool	extra_check(t_msh **msh, int *i, char c, t_quote *quotes)
{	
	if (ft_strchr(WS, c) && !quotes->in_quotes)
		*i = tk_space(msh, *i);
	else if (!ft_strchr(OPERATOR, c) && !quotes->in_quotes)
		*i = tk_word(msh, *i);
	else if (quotes->in_quotes) //deleted !ft_strchr(OPERATOR, c) && 
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
