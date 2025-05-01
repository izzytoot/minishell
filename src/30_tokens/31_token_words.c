/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_token_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:07:53 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/01 15:37:44 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int tk_space(t_msh **msh, int start)
{
	const char	*line;
	char		word[1000];
	int			i;
	int			j;
	t_tk_lst	*new_tk;
	
	line = (*msh)->prompt_line;
	i = start;
	j = 0;
    while (line[i] && ft_strchr(WHITESPACE, line[i]))
	{
		word[j++] = line[i];
		i++;
	}
	word[j] = '\0';
	new_tk = safe_malloc(sizeof(t_tk_lst));
	app_tk(*msh, new_tk, word, W_SPACE);
	return(i - 1);
}

int	tk_word(t_msh **msh, int start)
{
	const char	*line;
	char		word[1000];
	int			i;
	int			j;
	t_tk_lst	*new_tk;
	
	line = (*msh)->prompt_line;
	i = start;
	j = 0;
    while (line[i] && (!ft_strchr(OPERATOR, line[i])
		&& !ft_strchr(WHITESPACE, line[i]) && !ft_strchr(QUOTE, line[i])))
	{
		word[j++] = line[i];
		i++;
	}
	word[j] = '\0';
	new_tk = ft_calloc(1, sizeof(t_tk_lst));
	app_tk(*msh, new_tk, word, WORD);
	return(i - 1);
}

int	tk_word_qt(t_msh **msh, int start, 
	bool *in_quotes, char *quote_char)
{
	const char	*line;
	char		word[1000];
	int			i;
	int			j;
	t_tk_lst	*new_tk;
	
	line = (*msh)->prompt_line;
	i = start;
	j = 0;
    while (line[i] && (line[i] != *quote_char))
		word[j++] = line[i++];
	word[j] = '\0';
	new_tk = ft_calloc(1, sizeof(t_tk_lst));
	app_tk(*msh, new_tk, word, WORD);
	if (*quote_char == '\'')
		(*msh)->token_list->quotes.in_squotes = true;
	else if (*quote_char == '\"')
		(*msh)->token_list->quotes.in_dquotes = true;
	(*msh)->token_list->quotes.content = ft_strdup(word);
	*in_quotes = false;
	return(i - 1);
}
