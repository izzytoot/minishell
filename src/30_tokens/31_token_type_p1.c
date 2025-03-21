/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_token_type_p1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:07:53 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/20 19:25:49 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	token_is_word(t_minishell **msh, int start)
{
	const char	*line;
	char		word[1000];
	int			i;
	int			j;
	bool		in_quotes;
	char		quote_char;
	t_token_lst	*new_token;
	
	line = (*msh)->promt_line;
	in_quotes = false;
	quote_char = '\0';
	i = start;
	j = 0;
    while (line[i] && (!ft_strchr(OPERATOR, line[i]) || in_quotes) && (!ft_strchr(WHITESPACE, line[i]) || in_quotes))	
	{
		if (ft_strchr(QUOTE, line[i]))
			check_quote(&in_quotes, &quote_char, line[i]);
		else
			word[j++] = line[i];
		i++;
	}
	word[j] = '\0';
	new_token = calloc(1, sizeof(t_token_lst));
	append_token(*msh, new_token, word, WORD);
	return(i - 1);
}

int	token_is_pipe(t_minishell **msh, int start)
{
	int			i;
	int			j;
	char		pipe[5];
	t_token_lst	*new_token;
	const char *line;
	
	i = start;
	j = 0;
	line = (*msh)->promt_line;
	while(line[i] && line[i]== '|')
	{
		pipe[j++] = line[i];
		i++;
	}
	pipe[j] = '\0';
	new_token = calloc(1, sizeof(t_token_lst));
	append_token(*msh, new_token, pipe, PIPE);
	return(i - 1);
}

int	redir_r(t_minishell **msh, int start)
{
	int			i;
	const char *line;
	char		redir_app[5];
	char		redir_out[5];
	
	i = start;
	line = (*msh)->promt_line;
	if (line[i] && line[i + 1] == '>')
		i = token_is_redir_app(msh, line, redir_app, i);
	else
		i = token_is_redir_out(msh, line, redir_out, i);
	return(i);
}

int	token_is_redir_app(t_minishell **msh, const char *line, char *redir_app, int i)
{
	int		j;
	t_token_lst	*new_token;
	
	j = 0;
	while(line[i] && line[i] == '>')
	{
		redir_app[j++] = line[i];
		i++;
	}
	redir_app[j] = '\0';
	new_token = calloc(1, sizeof(t_token_lst));
	append_token(*msh, new_token, redir_app, REDIR_APP);
	return (i - 1);
}

int	token_is_redir_out(t_minishell **msh, const char *line, char *redir_out, int i)
{
	int		j;
	t_token_lst	*new_token;
	
	j = 0;
	while(line[i] && line[i] == '>')
	{
		redir_out[j++] = line[i];
		i++;
	}
	redir_out[j] = '\0';
	new_token = calloc(1, sizeof(t_token_lst));
	append_token(*msh, new_token, redir_out, REDIR_OUT);
	return (i - 1);
}
