/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_token_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:07:53 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/21 13:50:00 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int token_is_space(t_msh **msh, int start)
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
	return(i - 1);
}

int	token_is_word(t_msh **msh, int start)
{
	const char	*line;
	char		word[1000];
	int			i;
	int			j;
	t_tk_lst	*new_tk;
	
	line = (*msh)->prompt_line;
	i = start;
	j = 0;
    while (line[i] && (!ft_strchr(OPERATOR, line[i])) && !ft_strchr(WHITESPACE, line[i]))
	{
		word[j++] = line[i];
		i++;
	}
	word[j] = '\0';
	new_tk = calloc(1, sizeof(t_tk_lst));
	app_tk(*msh, new_tk, word, WORD);
	return(i - 1);
}

int	token_is_word_in_quotes(t_msh **msh, int start, bool *in_quotes, char *quote_char)
{
	const char	*line;
	char		word[1000];
	int			i;
	int			j;
	t_tk_lst	*new_tk;
	
	line = (*msh)->prompt_line;
	i = start;
	j = 0;
    while (line[++i] && (line[i] != *quote_char))
		word[j++] = line[i];
	word[j] = '\0';
	new_tk = calloc(1, sizeof(t_tk_lst));
	app_tk(*msh, new_tk, word, WORD);
	*in_quotes = false;
	return(i - 1);
}
