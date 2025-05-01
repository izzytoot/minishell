/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_token_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:07:53 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/01 13:20:50 by ddo-carm         ###   ########.fr       */
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
	new_tk = calloc(1, sizeof(t_tk_lst));
	app_tk(*msh, new_tk, word, W_SPACE);
	(*msh)->token_list->next->quotes.space_case = true;
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
		if (line[i] == '$' && (line[i + 1] == '?' || line[i + 1] == '0'))
		{
			special_cases(msh, &i, line[i + 1]);
			return(i - 1);
		}
		word[j++] = line[i];
		i++;
	}
	word[j] = '\0';
	new_tk = calloc(1, sizeof(t_tk_lst));
	app_tk(*msh, new_tk, word, WORD);
	return(i - 1);
}

int	special_cases(t_msh **msh, int *i, char c)
{
	t_tk_lst	*new_tk;
	char		*word;
	
	if (c == '?')
	{
		word = ft_strdup("$?");
		*i += 2;
	}
	else
	{
		word = ft_strdup("$0");
		*i += 2;
	}
	new_tk = calloc(1, sizeof(t_tk_lst));
	app_tk(*msh, new_tk, word, WORD);
	return(*i);
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
	new_tk = calloc(1, sizeof(t_tk_lst));
	app_tk(*msh, new_tk, word, WORD);
	if (*quote_char == '\'')
		(*msh)->token_list->quotes.in_squotes = true;
	else if (*quote_char == '\"')
		(*msh)->token_list->quotes.in_dquotes = true;
	(*msh)->token_list->quotes.content = ft_strdup(word);
	*in_quotes = false;
	return(i - 1);
}
