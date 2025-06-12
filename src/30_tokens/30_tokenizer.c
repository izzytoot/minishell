/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:33:00 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/12 16:44:49 by icunha-t         ###   ########.fr       */
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
	if (ch_empty_case(msh, line, 0, true))
		i = empty_case(msh, line, 0, true);
	while (line[++i])
	{
		sort_out_quotes(msh, line, &i, &quotes);
		if (i >= (int)ft_strlen(line))
			break ;
		if (line[i] && line[i] != quotes.quote_char
			&& (extra_check(&(*msh), &i, line[i], &quotes)))
				;
		else if (line[i] == quotes.quote_char)
			i--;
		else
			break ;
	}
	if ((*msh)->debug_mode)
	{
		print_tokens(&(*msh));
		ft_printf("------------------------------\n");
	}
	sub_tokenize(&(*msh));
	if ((*msh)->debug_mode)
	{
		print_tokens(&(*msh));
		ft_printf("------------------------------\n");
	}
	parse_line(&(*msh));
	return ;
}

bool	extra_check(t_msh **msh, int *i, char c, t_quote *quotes)
{
	if (c == '$' && !quotes->in_quotes)
		*i = exp_to_null(msh, *i);
	if (ft_strchr(WS, c) && (!quotes->in_quotes))
	{
		*i = tk_space(msh, *i);
	}
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

void	init_qt_struct(t_quote *quotes)
{
	quotes->in_squotes = false;
	quotes->in_dquotes = false;
	quotes->in_quotes = false;
	quotes->content = NULL;
	quotes->exp = false;
	quotes->quote_char = '\0';
	quotes->sp_case = false;
}

int	exp_to_null(t_msh **msh, int start)
{
	int			i;
	char		exp[5];
	t_tk_lst	*new_tk;
	const char	*line;

	i = start + 1;
	line = (*msh)->prompt_line;
	if (!line[i] || (line[i] && !ft_strchr(QT, line[i])))
		return (start);
	while (line[i] && !ft_strchr(WS, line[i]))
	{
		if ((line[i + 1] && ((line[i] != line[i + 1])))
			|| !ft_strchr(QT, line[i]))
			return (start);
		i++;
		if (ft_strchr(WS, line[i + 1]))
			break ;
	}
	exp[0] = '\0';
	new_tk = ft_calloc(1, sizeof(t_tk_lst));
	if (start == 0)
		app_tk(*msh, new_tk, "\'\'", ARG);
	else
		app_tk(*msh, new_tk, exp, ARG);
	return (i - 1);
}

void	app_tk(t_msh *msh, t_tk_lst *new_tk, char *content, t_tk_type type)
{
	new_tk->type = type;
	if (ft_strcmp("''", content) == 0)
		msh->empties = true;
	if (content)
	{
		new_tk->content = ft_strdup(content);
		new_tk->quotes.content = ft_strdup(content);
	}
	else
	{
		new_tk->content = NULL;
		new_tk->quotes.content = NULL;
	}
	new_tk->next = msh->token_list;
	new_tk->prev = NULL;
	if (msh->token_list)
		msh->token_list->prev = new_tk;
	msh->token_list = new_tk;
	if (type == REDIR_HD)
		msh->hd_check = true;
}
